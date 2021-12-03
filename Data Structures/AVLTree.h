#pragma once
#include <algorithm>

/*
* The deletion code isn't really well-tested and may contain errors
*/

template<typename T>
class AVLTree
{
	struct Node
	{
		T data;
		Node* left = NULL;
		Node* right = NULL;
		Node(const T& data)
			:
			data(data)
		{}
		~Node()
		{
			delete left;
			delete right;
		}
		int GetHeight() const
		{
			int h1 = (left) ? left->GetHeight() : 0;
			int h2 = (right) ? right->GetHeight() : 0;
			return 1 + std::max(h1, h2);
		}
		int GetBalanceFactor() const
		{
			int l = (left) ? left->GetHeight() : 0;
			int r = (right) ? right->GetHeight() : 0;
			return l - r;
		}
		void Inorder() const
		{
			if (left)
				left->Inorder();
			std::cout << data << ' ';
			if (right)
				right->Inorder();
		}

		static void Insert(Node*& n, const T& data_in)
		{
			if (data_in > n->data)
			{
				if (n->right == NULL)
					n->right = new Node(data_in);
				else
				{
					Insert(n->right, data_in);
					Balance(n);
				}
			}
			else
			{
				if (n->left == NULL)
					n->left = new Node(data_in);
				else
				{
					Insert(n->left, data_in);
					Balance(n);
				}
			}
		}
		static void Delete(Node*& n, const T& data)
		{
			if (n->data == data)
			{
				if (n->right == nullptr)
				{
					Node* temp = n;
					n = n->left;
					temp->left = nullptr;
					delete temp;
				}
				else
				{
					auto min = FindMin(n->right);
					Delete(n->right, min);
					n->data = min;
				}
			}
			else if (n->right != nullptr && data > n->data)
			{
				Delete(n->right, data);
			}
			else if(n->left != nullptr)
			{
				Delete(n->left, data);
			}

			if (n)
				Balance(n);
		}

		static T FindMin(const Node* n)
		{
			if (n->left == nullptr)
			{
				return n->data;
			}
			else
				return FindMin(n->left);
		}
		
		static void RotateRight(Node*& pivot)
		{
			Node* old_pivot = pivot;
			pivot = pivot->left;
			old_pivot->left = pivot->right;
			pivot->right = old_pivot;
		}
		static void RotateLeft(Node*& pivot)
		{
			Node* old_pivot = pivot;
			pivot = pivot->right;
			old_pivot->right = pivot->left;
			pivot->left = old_pivot;
		}
		static void DoubleRotateRightLeft(Node*& pivot)
		{
			RotateRight(pivot->right);
			RotateLeft(pivot);
		}
		static void DoubleRotateLeftRight(Node*& pivot)
		{
			RotateLeft(pivot->left);
			RotateRight(pivot);
		}
		static void Balance(Node*& n)
		{
			if (n->GetBalanceFactor() == -2)
			{
				if (n->right->GetBalanceFactor() == -1)
				{
					RotateLeft(n);
				}
				else
				{
					DoubleRotateRightLeft(n);
				}
			}
			else if (n->GetBalanceFactor() == 2)
			{
				if (n->left->GetBalanceFactor() == 1)
				{
					RotateRight(n);
				}
				else
				{
					DoubleRotateLeftRight(n);
				}
			}
		}
	};

public:
	AVLTree() = default;
	AVLTree(const AVLTree&) = delete;
	AVLTree& operator=(const AVLTree&) = delete;

	void Insert(const T& data)
	{
		if (root == NULL)
			root = new Node(data);
		else
			Node::Insert(root, data);
	}

	void Delete(const T& data)
	{
		Node::Delete(root, data);
	}

	void Inorder() const
	{
		root->Inorder();
		std::cout << std::endl;
	}

private:
	Node* root = NULL;
};