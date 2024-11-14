#ifndef BST_H
#define BST_H

#include <functional>
#include <iostream>




class BST
{
public:
	class Node
	{
	public:
		Node(int value, Node* left, Node* right);
		Node();
		Node(const Node& node);
		Node(int value);

		int value;
		Node* left;
		Node* right;

		friend std::ostream& operator<<(std::ostream& out, const Node& node);
		bool operator>(int num){
			return value > num;
		};
		bool operator<(int num){
			return value < num;
		}
		bool operator>=(int num){
			return value >= num;
		}
		bool operator<=(int num){
			return value <= num;
		}
		bool operator==(int num){
			return value == num;
		}
		friend bool operator<(int num, const Node& node);
		friend bool operator>(int num, const Node& node);
		friend bool operator<=(int num, const Node& node);
		friend bool operator>=(int num, const Node& node);
		friend bool operator==(int num, const Node& node);
	};
	BST();
	BST(BST& bst);
	BST(BST&& bst) noexcept;
	BST(std::initializer_list<int> list);
	Node* deep_copy(BST::Node* &node);
    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func) const;
	void dfs(std::function<void(Node*& node)> func) const;
    size_t length();
	size_t length(Node* node);
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);
	friend std::ostream& operator<<(std::ostream& out,const BST& bst);
	BST operator++();
	BST operator++(int);
	BST& operator=(const BST& bst);
	BST& operator=(BST&& bst) noexcept;
	~BST();
private:
    Node* root;
};





#endif //BST_H