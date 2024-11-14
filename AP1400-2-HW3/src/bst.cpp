#include "bst.h"
#include <queue>
#include <stack>
#include <iomanip>



BST::Node::Node(int value, Node *left, Node *right):
value(value),left(left),right(right){}

BST::Node::Node():value(0),left(nullptr),right(nullptr){}

BST::Node::Node(const Node &node):
value(node.value),left(node.left),right(node.right){}
/*value(node.value),left(nullptr),right(nullptr){   //这里实现的是一个深拷贝,但是测试里面的意思好像是浅拷贝
    if(node.left!=nullptr){
        left = new Node(*node.left);
    }
    if(node.right!=nullptr){
        right = new Node(*node.right);
    }
}*/

BST::Node::Node(int value):value(value),left(nullptr),right(nullptr){}

BST::BST():root(nullptr){}

BST::BST(BST &bst){
    this->root = deep_copy(bst.root);
}

BST::Node* BST::deep_copy(BST::Node* &node)   //初始化依赖于深拷贝,但是Node的默认是浅拷贝
{
    if (node == nullptr) {
        return nullptr;
    }
    BST::Node *copyNode = new BST::Node(node->value, nullptr, nullptr);
    copyNode->left = deep_copy(node->left);
    copyNode->right = deep_copy(node->right);
    return copyNode;
}

//对于这个移动拷贝构造,将根节点的所有权转移后好像就转移了整颗树?
//如果根节点为nullptr,~BST()将不起作用
BST::BST(BST &&bst) noexcept:root(bst.root){
    bst.root = nullptr;   //源对象的根节点设置为nullptr,防止重复释放
}

BST::BST(std::initializer_list<int> list)
{
    root = nullptr;
    for(int value:list){
        this->add_node(value);
    }
}

BST::Node*& BST::get_root()
{
    return root;
}

void BST::bfs(std::function<void(Node *&node)> func) const
{
    if(root == nullptr){
        return;
    }
    std::queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        auto node_front = q.front();
        q.pop();
        func(node_front);
        if(node_front->left!=nullptr){
            q.push(node_front->left);
        }
        if(node_front->right!=nullptr){
            q.push(node_front->right);
        }
    }
}

//写一个dfs版本的
void BST::dfs(std::function<void(Node *&node)> func) const
{
    if (root == nullptr){
        return;
    }
    std::stack<Node*> s;
    s.push(root);
    while(!s.empty()){
        auto node_top = s.top();
        s.pop();
        func(node_top);
        if(node_top->left!=nullptr){
            s.push(node_top->left);
        }
        if(node_top->right!=nullptr){
            s.push(node_top->right);
        }

    }
}

size_t BST::length()
{
    /*size_t size = 0;     //使用bfs开销小一点,也可以选用递归法
    bfs([&size](BST::Node*& node){size++;});
    return size;*/
    return length(root);
}

size_t BST::length(Node* node){
    if(node == nullptr){
        return 0;
    }else{
        return 1+length(node->left) + length(node->right);
    }
}

bool BST::add_node(int value)
{
    if (root == nullptr){
        root = new Node(value,nullptr,nullptr);
        return true;
    }
    auto p = root;
    BST::Node* parent_p = nullptr;
    while(p!=nullptr){
        if(value<p->value){
            parent_p = p;
            p = p->left;
        }else if(value>p->value){
            parent_p = p;
            p = p->right;
        }else{
            return false;
        }
    }
    if(value<parent_p->value){
        parent_p->left = new Node(value,nullptr,nullptr);
    }else{
        parent_p->right = new Node(value,nullptr,nullptr);
    }
    return true;

}


BST::Node **BST::find_node(int value)
{
    auto p = get_root();
    Node* prev_p;
    if(p->value==value){
        return &root;
    }
    while(p!=nullptr){
        if (p->value == value){
            break;        //不能在这里直接返回p的原因:p是在函数内申明的,会被回收
        }else if(p->value<value){
            prev_p = p;
            p = p->right;
        }else{
            prev_p = p;
            p = p->left;
        }
    }
    if(p==nullptr){
        return nullptr;
    }
    if (prev_p->left&&prev_p->left->value==value){
        return &(prev_p->left);
    }else if(prev_p->right&&prev_p->right->value==value){
        return &(prev_p->right);
    }
    return nullptr;
}

BST::Node **BST::find_parrent(int value)
{
    auto p = root;
    BST::Node* parent_p = nullptr;
    if(p->value==value){
        return nullptr;
    }
    while(p!=nullptr){
        if (p->value == value){
            return find_node(parent_p->value);
        }else if(p->value<value){
            parent_p = p;
            p = p->right;
        }else{
            parent_p = p;
            p = p->left;
        }
    }
    return nullptr;
}

BST::Node **BST::find_successor(int value)
//主要算法思想:如果该节点存在右子树,则下一个节点的位置在右子树最左的节点(一直往左走)
//如果没有右子树,循环找父节点,如果父节点的右子树是,则该节点为后继
{
    /*BST::Node** p = find_node(value);
    if(p==nullptr){
        return nullptr;
    }
    if((*p)->right!=nullptr){
        BST::Node* p_successor = (*p)->right;
        while(p_successor->left!=nullptr){
            p_successor = p_successor->left;
        } 
        return find_node(p_successor->value);
    }else{
    int value_succesor = value;
        while(find_parrent(value_succesor)!=nullptr){
            BST::Node** pp_successor = find_parrent(value_succesor);
            if((*pp_successor)->left!=nullptr&&(*pp_successor)->left->value==value_succesor){
                return find_node((*pp_successor)->value);
            }else{
                value_succesor = (*pp_successor)->value;
            }
        }
    }
    return nullptr;*/   //这个是寻找数值下一个的节点,反过来就是寻找数值为上一个的节点了
    BST::Node** p = find_node(value);
    if(p==nullptr){
        return nullptr;
    }
    if((*p)->left!=nullptr){
        BST::Node* p_successor = (*p)->left;
        while(p_successor->right!=nullptr){
            p_successor = p_successor->right;
        }
        return find_node(p_successor->value);
    }else{
        int value_succesor = value;
        while(find_parrent(value_succesor)!=nullptr){
            BST::Node** pp_successor = find_parrent(value_succesor);
            if((*pp_successor)->right!=nullptr&&(*pp_successor)->right->value==value_succesor){
                return find_node((*pp_successor)->value);
            }else{
                value_succesor = (*pp_successor)->value;
            }
        }
    }
    return nullptr;
}

bool BST::delete_node(int value)
{
    auto node_p2 = find_node(value);
    if(node_p2 == nullptr){
        return false;
    }
    auto node_p = *node_p2;
    //左右子节点都是nullptr,在前面已经处理掉了是root节点的可能性
    if(node_p->left==nullptr&&node_p->right==nullptr){
       *node_p2 = nullptr;
        delete node_p;
    }
    //如果有左节点
    else if(node_p->left==nullptr&&node_p->right!=nullptr){
       *node_p2 = node_p->right;
       delete node_p;
    }
    //如果有右节点
    else if(node_p->left!=nullptr&&node_p->right==nullptr){
        *node_p2 = node_p->left;
        delete node_p;
    }
    //左右节点都存在,左子树最大或者右子树最小替换原节点
    //因为存在左节点,直接find_successor
    else{
        auto node_successor = *find_successor(value);
        auto node_successor_parent = *find_parrent(node_successor->value);
        std::swap(node_successor->value,node_p->value);
        node_successor_parent->right=nullptr;
        delete node_successor;
        return true;
    }
    return true;
}

//a++和++a重载是不同的,以示区分a++参数要传入一个int,用来标注
BST BST::operator++()
{
    bfs([this](BST::Node*& node){
        node->value++;
    });
    return *this;
}

/*注意:如bst2{bst1++}这种情况,应该是:
bst2=bst1;
bst1++;
所以应该是直接赋值一个bst返回,但是在之前需要给this的节点+1;
此外BST bst = *this;更好,返回的是右值赋值,
详见https://github.com/half-dreamer/AP1400-2-HW3/issues/1
*/
BST BST::operator++(int)
{
    BST bst = *this;
    this->bfs([&bst](BST::Node*& node){
        node->value++;
    });
    return bst;
}

//需要返回BST&,gpt说因为如果operator=返回的不是引用，
//那么链式赋值将无法工作，因为链式赋值依赖于每个赋值运算符返回左侧对象的引用。
BST& BST::operator=(const BST &bst)
{
    //要注意删掉可能存在的原来的树,避免内存泄漏
    if (this != &bst) { // 防止自赋值
        this->~BST();
        root = bst.root ? new Node(*bst.root) : nullptr; // 深拷贝新树
    }
    return *this;
}

BST& BST::operator=(BST &&bst) noexcept
{
    if(this != &bst){
        this->~BST();
        root = std::move(bst.root);
        bst.root = nullptr;
    }
    return *this;
}

BST::~BST()
 {
 	std::vector<Node*> nodes;
 	bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
 	for(auto& node: nodes)
 		delete node;
 }

std::ostream& operator<<(std::ostream& out, const BST::Node& node){
    //out<<node.value<<"   "<<&node.left<<"   "<<&node.right;
    out<<&node<<std::setw(12)<<"=> ";
    out<<std::setw(12)<<node.value;
    if(node.left!=nullptr){
        out<<std::setw(18)<<"left:"<<&node.left;
    }else{
        out<<std::setw(18)<<"left:"<<0;
    }
    if(node.right!=nullptr){
        out<<std::setw(18)<<"right:"<<&node.right<<std::endl;
    }else{
        out<<std::setw(18)<<"right:"<<0<<std::endl;
    }
    return out;
}
bool operator<(int num, const BST::Node& node){
    return num<node.value;
}
bool operator>(int num, const BST::Node& node){
    return num>node.value;
}
bool operator<=(int num, const BST::Node& node){
    return num<=node.value;
}
bool operator>=(int num, const BST::Node& node){
    return num>=node.value;
}
bool operator==(int num, const BST::Node& node){
    return num==node.value;
}
//bfs要求的是一个函数func,可以传入一个lambda匿名函数
//捕获列表的意思:外部定义的变量想要在内部使用分为[&]引用捕获,[=]值捕获,[this]当前对象指针
std::ostream& operator<<(std::ostream& out,const BST& bst){
    out<<"********************************************************************************"<<std::endl;
    bst.bfs([&out](BST::Node*& node){
        out<<*node;
    });
    out<<"********************************************************************************"<<std::endl;
    return out;
}

