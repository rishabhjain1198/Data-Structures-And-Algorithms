// MyMap.h

// Skeleton for the MyMap class template.  You must implement the first six
// member functions.

#include<iostream>

template<typename KeyType, typename ValueType>
class MyMap
{
public:
	MyMap()
    {
        m_size = 0;
        root = nullptr;
    }
    
	~MyMap()
    {
        clear();
    }
    
	void clear()
    {
        deleteTreeNode(root);
        m_size = 0;
    }
    
	int size() const
    {
        return m_size;
    }
    
	void associate(const KeyType& key, const ValueType& value)
    {
        m_size++;
        
        Node* toBeInserted = new Node;
        toBeInserted -> key = key;
        toBeInserted -> value = value;
        toBeInserted -> leftChild = nullptr;
        toBeInserted -> rightChild = nullptr;
        
        if(root == nullptr)
        {
            root = toBeInserted;
            //std::cout<<"shi";
            return;
        }
        
        Node* currentNode = root;
        Node *parentNode = nullptr;
        bool isOnLeft = 0;
        
        while(true)
        {
            if(currentNode == nullptr)
            {
                if(isOnLeft)
                    parentNode -> leftChild = toBeInserted;
                else
                    parentNode -> rightChild = toBeInserted;
                
                return;
            }
                        //std::cout<<std::endl<<"current node value: "<<currentNode -> key;
            if(currentNode -> key == toBeInserted -> key)
            {
                currentNode -> value = toBeInserted -> value;
                delete toBeInserted;
                return ;
            }
            
            if(currentNode -> key > toBeInserted -> key)
            {
                parentNode = currentNode;
                isOnLeft = 1;
                currentNode = currentNode -> leftChild;
                //std::cout<<"left gaya";
            }
            
            else
            {
                parentNode = currentNode;
                isOnLeft = 0;
                currentNode = currentNode -> rightChild;
                //std::cout<<" called";
            }
        }
    }

	  // for a map that can't be modified, return a pointer to const ValueType
	const ValueType* find(const KeyType& key) const
    {
        KeyType key1 = key;
        Node* currentNode = root;
        
        while(true)
        {
            if(currentNode == nullptr)
                return nullptr;
            
           // std::cout<<currentNode -> key<<std::endl;
            
            if(currentNode -> key == key1)
                return &(currentNode -> value);
            
            if(currentNode -> key > key1)
                currentNode = currentNode -> leftChild;
            else
                currentNode = currentNode -> rightChild;
        }
        
    }

	  // for a modifiable map, return a pointer to modifiable ValueType
	ValueType* find(const KeyType& key)
	{
		return const_cast<ValueType*>(const_cast<const MyMap*>(this)->find(key));
	}

	  // C++11 syntax for preventing copying and assignment
	MyMap(const MyMap&) = delete;
	MyMap& operator=(const MyMap&) = delete;

private:
    struct Node
    {
        KeyType key;
        ValueType value;
        
        Node* leftChild;
        Node* rightChild;
    };
    int m_size;
    Node* root;
    
    void deleteTreeNode(Node* toBeDeleted)
    {
        if(toBeDeleted == nullptr)
            return;
        
        deleteTreeNode(toBeDeleted -> leftChild);
        
        deleteTreeNode(toBeDeleted -> rightChild);
        
        delete toBeDeleted;
    }
};
