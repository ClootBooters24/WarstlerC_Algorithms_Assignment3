#include <bst.hpp>

BSTNode::BSTNode() {
    this->left = this->right = NULL;
    this->height = 0;
}

BSTNode::BSTNode(int key, int height, int meta, BSTNode *left, BSTNode *right) {
    this->key = key;
    this->height = height;
    this->meta = meta;
    this->left = left;
    this->right = right;
}


BSTNode::~BSTNode() {
    this->left = this->right = NULL;
}

/*
    The constructor of BST initializes the empty BST, the implementation of the constructor is provided.
*/
BST::BST() {
    // YOU DO NOT NEED TO IMPLEMENT THIS ONE
    this->root = NULL;
}

/*
    The deconstructor of BST will deallocate memory of all nodes in the BST.
    You have to implement the deconstructor to release memory of all nodes.
*/
BST::~BST() {
    // YOUR CODE HERE
    delete this->root;
}

/*
    The find method will find the node that contains the key. 
    You have to implement the find method to return the node containing the given key.
*/
BSTNode* BST::find(int key) {
    // YOUR CODE HERE
    // std::cout << "\nCall Find Helper\n";
    return findHelper(this->root, key);
}

BSTNode* BST::findHelper(BSTNode* current, int key) {
    if(current == nullptr) {
        // std::cout << "Found: " << current;
        return nullptr;
    }

    if(key == current->key) {
        return current;
    }

    if(key < current->key) {
        // std::cout << "Find Left\n";
        return findHelper(current->left, key);
    } else {
        // std::cout << "Find Right\n";
        return findHelper(current->right, key);
    }
}

/*
    The pop maximum method will return the node that contains the maximum value 
    and remove that node out BST but DO NOT release the memory of this maximum node. 
    You have to implement the pop maximum method to return the node containing the maximum value and remove it out of the BST.
*/
BSTNode* BST::popMaximum() {
    // YOUR CODE HERE
    if(this->root == nullptr) {
        return nullptr;
    }

    BSTNode* max = this->root;
    BSTNode* parent = nullptr;

    //Go to the right
    while(max->right != nullptr) {
        // std::cout << "\ngoing right\n";
        parent = max;
        max = max->right;
    }

    if(max == this->root) {
        // std::cout << "\nFound Max\n";
        this->root = max->left;
    } else {
        parent->right = max->left;
    }

    max->left = max->right = nullptr;

    // std::cout << "Maximum Popped: " << current;
    return max;
}

/* 
    The pop minimum method will return the node that contains the minimum value 
    and remove that node out BST but DO NOT release the memory of this minimum node. 
    You have to implement the pop minium method to return the node containing the minum value and remove it out of the BST.
*/
BSTNode* BST::popMinimum() {
    // YOUR CODE HERE
    // std::cout << "\nIn popMin\n";
    if(this->root == nullptr) {
        return nullptr;
    }

    BSTNode* min = this->root;
    BSTNode* parent = nullptr;

    //Go to the left
    while(min->left != nullptr) {
        parent = min;
        min = min->left;
    }

    if(min == this->root) {
        this->root = min->right;
    } else {
        parent->left = min->right;
    }

    min->left = min->right = nullptr;

    // std::cout << "Minimum Popped: " << current;
    return min;
}

/*
    The insert method will insert a new node containing the key and meta data. 
    You have to implement the insert method to insert a new node with a given key and meta data into BST and return the new root of BST. 
*/
BSTNode* BST::insert(int key, int meta) {
    // YOUR CODE HERE
    // std::cout << "\nCall Insert Helper\n";
    this->root = insertHelper(this->root, key, meta);
    return this->root;
}

BSTNode* BST::insertHelper(BSTNode* current, int key, int meta) {
    if(current == nullptr) {
        return new BSTNode(key, 0, meta);
    }

    if(key <= current->key) {
        // std::cout << "Insert Left\n";
        current->left = insertHelper(current->left, key, meta);
    } else if(key > current->key) {
        // std::cout << "Insert Right\n";
        current->right = insertHelper(current->right, key, meta);
    }

    // std::cout << "Inserted: " << current;
    return current;
}

/*
    The remove method will remove a new node containing the key and meta data. 
    You have to implement the remove method to remove a node containing the given key out of BST and return the new root of BST.
*/
BSTNode* BST::remove(int key) {
    // YOUR CODE HERE
    // std::cout << "\nCall Remove Helper\n";
    this->root = removeHelper(this->root, key);

    return this->root;
}

BSTNode* BST::removeHelper(BSTNode* current, int key) {
    if(current == nullptr) {
        return nullptr;
    }

    if(key < current->key) {
        current->left = removeHelper(current->left, key);
    } else if(key > current->key) {
        current->right = removeHelper(current->right, key);
    } else{
        if(current->left == nullptr) {
            BSTNode* temp = current->right;
            delete current;
            return temp;
        } else if(current->right == nullptr) {
            BSTNode* temp = current->left;
            delete current;
            return temp;
        }

        BSTNode* temp = findMin(current->right);
        current->key = temp->key;
        current->right = removeHelper(current->right, temp->key);
    }

    // std::cout << "Removed: " << current;
    return current;
}

BSTNode* BST::findMin(BSTNode* node) {
    while(node != nullptr && node->left != nullptr) {
        node = node->left;
    }

    return node;
}