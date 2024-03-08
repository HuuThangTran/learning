// Anh Le // First and Last name
// mle288 // UCSC UserID
// 2024 Winter CS101 PA7
// Dictionary.cpp // FileName
// The black box file contains the logic for user client code // Describe the program


#include<iostream>
#include<string>
#include"Dictionary.h"


using namespace std;

// Class Constructors & Destructors ----------------------------------------
   

    // private Node struct
    Dictionary::Node::Node(keyType k, valType v){
        key = k;
        val = v;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }

    // Creates new Dictionary in the empty state. 
    Dictionary::Dictionary() {
        // Node(keyType k, valType v);
        nil = new Node("", 0);
        // nil = nullptr;
        root = nil;
        current = nil;
        num_pairs = 0;
    }

    // Copy constructor.
    Dictionary::Dictionary(const Dictionary& D) {
        // Node(keyType k, valType v);
        //dummmy 
        nil = new Node("", 0);
        // nil = nullptr;
        root = nil;
        current = nil; 
        num_pairs = 0;

        preOrderCopy(D.root, D.nil);
    }

    // Destructor
    Dictionary::~Dictionary() {
        // delete start from root
        postOrderDelete(this->root);
        delete nil;
        nil = nullptr;
        current = nullptr;
        root = nullptr;
    }


// Helper Functions (Optional) ---------------------------------------------

    // inOrderString()
    // Appends a string representation of the tree rooted at R to string s. The
    // string appended consists of: "key : value \n" for each key-value pair in
    // tree R, arranged in order by keys.
    void Dictionary::inOrderString(std::string& s, Node* R) const{
        //check to see if  N is null;
        if (R != nil) {
            inOrderString(s, R->left);
            s.append(R->key + " : " + std::to_string(R->val) + "\n");
            inOrderString(s, R->right);
        }    
    }


    // preOrderString()
    // Appends a string representation of the tree rooted at R to s. The appended
    // string consists of keys only, separated by "\n", with the order determined
    // by a pre-order tree walk.
    void Dictionary::preOrderString(std::string& s, Node* R) const {
        if (R != nil) {
            s.append(R->key + "\n");
            preOrderString(s, R->left);
            preOrderString(s, R->right);
        }   

    }

    // preOrderCopy()
    // Recursively inserts a deep copy of the subtree rooted at R into this 
    // Dictionary. Recursion terminates at N.
    void Dictionary::preOrderCopy(Node* R, Node* N) {
        if (R != N) {
            setValue(R->key, R->val);
            preOrderCopy(R->left, N);
            preOrderCopy(R->right, N);
        }
    }

    // postOrderDelete()
    // Deletes all Nodes in the subtree rooted at R.
    void Dictionary::postOrderDelete(Node* R){
        if(R != nil) {
            postOrderDelete(R->left);
            postOrderDelete(R->right);
            delete R;
            num_pairs --;
        }
    }

    // search()
    // Searches the subtree rooted at R for a Node with key==k. Returns
    // the address of the Node if it exists, returns nil otherwise.
    Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
        /*
        if x == NIL or k == x.key
        return x
        else if k < x.key
            return TreeSearch(x.left, k)
        else // k > x.key
            return TreeSearch(x.right, k)
        */
        if (R == nil || k == R->key) {
            return R;
        } else if (k < R->key) {
            return search (R->left, k);
        } else if (k > R->key) {
            return search (R->right, k);
        }
        return nil;
    }

    // findMin()
    // If the subtree rooted at R is not empty, returns a pointer to the 
    // leftmost Node in that subtree, otherwise returns nil.
    Dictionary::Node* Dictionary::findMin(Node* R) {
        /*
        TreeMaximum(x) Pre: x != NIL
        while x.right != NIL
            x = x.right
        return x
        */
        // pre
        if( R == nil ) {
            return nil;
        }
        while (R->left != nil) {
            R = R->left;
        }
        return R;
    }

    // findMax()
    // If the subtree rooted at R is not empty, returns a pointer to the 
    // rightmost Node in that subtree, otherwise returns nil.
    Dictionary::Node* Dictionary::findMax(Node* R) {
        /*  
            TreeMaximum(x) Pre: x != NIL
            while x.right != NIL
            x = x.right
            return x
        */
        if ( R == nil) {
            return nil;
        }
        while (R->right != nil) {
            R = R->right;
        }
        return R;
    }

    // findNext()
    // If N does not point to the rightmost Node, returns a pointer to the
    // Node after N in an in-order tree walk.  If N points to the rightmost 
    // Node, or is nil, returns nil. 
    Dictionary::Node* Dictionary::findNext(Node* N) {
        /*
        TreeSuccessor(x)
        if x.right != NIL                 // case 1
            return TreeMinimum(x.right)
        y = x.parent                      // case 2
        while y != NIL and x == y.right
            x = y
            y = y.parent
        return y
        */
        //case 1
        if (N->right != nil) {
            return findMin(N->right);
        }
        //case 2
        Node* M = N->parent;
        while (M != nil && N == M->right) {
            N = M;
            M = M->parent;
        }
        return M;
    }

    // findPrev()
    // If N does not point to the leftmost Node, returns a pointer to the
    // Node before N in an in-order tree walk.  If N points to the leftmost 
    // Node, or is nil, returns nil.
    Dictionary::Node* Dictionary::findPrev(Node* N) {
        // case 1
        if (N->left != nil) {
        return findMax(N->left);
        }
        // case 2
        Node* M = N->parent;
        while (M != nil && N == M->left) {
            N = M;
            M = M->parent;
        }
        return M;
    }




    // Access functions --------------------------------------------------------

    // size()
    // Returns the size of this Dictionary.
    int Dictionary::size() const {
        return this->num_pairs;
    }

    // contains()
    // Returns true if there exists a pair such that key==k, and returns false
    // otherwise.
    bool Dictionary::contains(keyType k) const {
        return search(this->root, k) != nil;
    }

    // getValue()
    // Returns a reference to the value corresponding to key k.
    // Pre: contains(k)
    valType& Dictionary::getValue(keyType k) const {
        // search the whole tree to fine the node with value K in it
        if (! contains(k)) {
            throw std::logic_error(".getValue() pre: contains(k)");
        }
        Node* keyK = search(this->root, k);
        return keyK->val;
    }

    // hasCurrent()
    // Returns true if the current iterator is defined, and returns false 
    // otherwise.
    bool Dictionary::hasCurrent() const {
        return this->current != nil;
    }

    // currentKey()
    // Returns the current key.
    // Pre: hasCurrent() 
    keyType Dictionary::currentKey() const{
        if (!hasCurrent()){
            throw std::logic_error(".currentKey() Pre: hasCurrent()");
        }
        return this->current ->key;
    }

    // currentVal()
    // Returns a reference to the current value.
    // Pre: hasCurrent()
    valType& Dictionary::currentVal() const {
        if (!hasCurrent()){
                throw std::logic_error(".currentVal() Pre: hasCurrent()");
            }
            return this->current ->val;
    }

    //--------------------------------
    // Manipulation procedures -------------------------------------------------
    //--------------------------------

    // clear()
    // Resets this Dictionary to the empty state, containing no pairs.
    void Dictionary::clear() {
        postOrderDelete(this->root);
        num_pairs = 0;
        root = nil;
        current = nil;
    }

    // setValue()
    // If a pair with key==k exists, overwrites the corresponding value with v, 
    // otherwise inserts the new pair (k, v).
    void Dictionary::setValue(keyType k, valType v) {
        /*
        TreeInsert(T, z)
        y = NIL
        x = T.root
        while x != NIL
            y = x
            if z.key < x.key
                x = x.left
            else 
                x = x.right
        z.parent = y
        if y == NIL             // T was empty
            T.root = z    
        else if z.key < y.key
            y.left = z
        else 
            y.right = z
            */


        Node* insertNode = new Node(k, v);
        insertNode->left = nil;
        insertNode->right = nil;

        // have traversing node and keep track of its' parent
        Node* traversing = root;
        Node* traversing_parent = nil;
        // traversing the tree to find if node contain the key exist
        while (traversing != nil) {
            traversing_parent = traversing;
            if (k < traversing->key) {
                traversing = traversing->left;
            }
            else if (k > traversing-> key) {
                traversing = traversing-> right;
            }
            else {
                //key found => we dont need inserNode
                traversing->val = v;
                delete insertNode;
                return;
            }   
        }


        // key not found we need to insert insertNode
        insertNode->parent = traversing_parent;
        if (traversing_parent == nil) {
            this->root = insertNode;
        } else if (k < traversing_parent->key) {
            traversing_parent->left = insertNode;
        }else {
            traversing_parent->right = insertNode;
        }
        num_pairs++;
    }

    void transplant(Dictionary* T, Dictionary::Node* u, Dictionary::Node* v){
        /*
        ----------------------
        Transplant(T, u, v)
        ----------------------
        if u.parent == NIL
            T.root = v
        else if u == u.parent.left
            u.parent.left = v
        else 
            u.parent.right = v
        if v != NIL
            v.parent = u.parent
        */
        if(u->parent == nullptr){
            T->root = v;
        }else if(u == u->parent->left){
            u->parent->left = v;
        }else{
            u->parent->right = v;
        }
        if(v != nullptr){
            v->parent = u->parent;
        }
    }

    // remove()
    // Deletes the pair for which key==k. If that pair is current, then current
    // becomes undefined.
    // Pre: contains(k).
    void Dictionary::remove(keyType k) {
        // /*
        // Delete(T, z)
        // if z.left == NIL               // case 1  or case 2.1 (right only)
        //     Transplant(T, z, z.right)
        // else if z.right == NIL         // case 2.2 (left only)
        //     Transplant(T, z, z.left)
        // else                           // case 3
        //     y = TreeMinimum(z.right)
        //     if y.parent != z
        //         Transplant(T, y, y.right)
        //         y.right = z.right
        //         y.right.parent = y
        //     Transplant(T, z, y)
        //     y.left = z.left
        //     y.left.parent = y
        // */
        // // Pre: contains(k).
        // if (! contains(k)) {
        //     throw std::logic_error(".remove() pre: contains(k)");
        // }
        
        // // find the current node with k value
        // Node* N = search(this->root, k);
        // if (N == nil) {
        //     throw std::logic_error(".remove() pre: contains(k)");
        // }
        // // case 1 right only
        // // if z.left == NIL               // case 1  or case 2.1 (right only)
        // //     Transplant(T, z, z.right)
        // if (N->left == nil) {
        //     transplant(this, N, N->right);
        // } 
        // // else if z.right == NIL         // case 2.2 (left only)
        // //     Transplant(T, z, z.left)
        // else if (N->right == nil) {
        //     transplant(this, N, N->left);
        // }
        // // else                           // case 3
        // //     y = TreeMinimum(z.right)
        // //     if y.parent != z
        // //         Transplant(T, y, y.right)
        // //         y.right = z.right
        // //         y.right.parent = y
        // //     Transplant(T, z, y)
        // //     y.left = z.left
        // //     y.left.parent = y
        // else {
        //     Node* Y = findMin(N->right);
        //     if(Y->parent != N){
        //         transplant(this, Y, Y->right);
        //         Y->right = N->right;
        //         Y->right->parent = Y;
        //     }
        //     transplant(this, N, Y);
        //     Y->left = N->left;
        //     Y->left->parent = Y;
        // }

        // if(N == current){
        //     current = nil;
        // }
        
        // if(N->parent != nil && N->parent->right == N){
        //     N->parent->right = nil;
        // }

        // else if(N->parent != nil && N->parent->left == N){
        //     N->parent->left = nil;
        // }

        // delete N;
        // num_pairs --;
        // Pre: contains(k).


        // if (! contains(k)) {
        //     throw std::logic_error(".remove() pre: contains(k)");
        // }
        // Node* nodeToDel = search(root, k);

        // // set the current to nil in advance if is point to the same nodetodel
        // if (nodeToDel == current) {
        //     current = nil;
        // }

        // // 4 cases
        
        // //case 1: nodeToDel is the last node with no childen
        // if (nodeToDel->left == nil && nodeToDel->right == nil) {
        //     // check for root
        //     if (nodeToDel == root) {
        //         root = nil;
        //     } 
        //     // if it has parent
        //     else {
        //         // set the parent to nil
        //         if (nodeToDel->parent->left == nodeToDel) {
        //             nodeToDel->parent->left = nil;
        //         } else {
        //             nodeToDel->parent->right = nil;
        //         }
        //     }
            
        //     //finally delete
        //     delete nodeToDel;
        // }


        // //case 2: nodeToDel has children but only left 
        // else if (nodeToDel->right == nil) {
        //     // check for root
        //     if (nodeToDel == root) {
        //         root = nodeToDel->left;
        //     } 
        //     // in the middle => has parent
        //     else {

        //         // set the parent to to point to point to the children
        //         if (nodeToDel->parent->left == nodeToDel) {
        //             nodeToDel->parent->left = nodeToDel->left;
        //         } else {
        //             nodeToDel->parent->right = nodeToDel->left;
        //         }
        //     }

        //     nodeToDel->left->parent = nodeToDel->parent;
        //     delete nodeToDel;
        // }

        // // case 3 only right child
        // else if (nodeToDel->left == nil) {
        //     // check for root
        //     if (nodeToDel == root) {
        //         root = nodeToDel->right;
        //     } 
        //     // it has parent
        //     else {

        //         // set the parent to point to the children
        //         if (nodeToDel->parent->left == nodeToDel) {
        //             nodeToDel->parent->left = nodeToDel->right;
        //         } else {
        //             nodeToDel->parent->right = nodeToDel->right;
        //         }
        //     }


        //     nodeToDel->right->parent = nodeToDel->parent;
        //     delete nodeToDel;
        // }

        // // case 4: has children both side => traversing all the right side
        // // let the min child of right side be the first children
        // else {
        //     Node* minChild = findMin(nodeToDel->right);

        //     // check for condition
        //     if (minChild->parent != nodeToDel) {
        //         minChild->parent->left = minChild->right;
                
                
        //         if (minChild->right != nil) {
        //             minChild->right->parent = minChild->parent;
        //         }

                
        //         minChild->right = nodeToDel->right;
        //         minChild->right->parent = minChild;
        //     }

        //     if (nodeToDel == root) {
        //         root = minChild;
        //     } 
            
        //     else {
        //         if (nodeToDel->parent->left == nodeToDel) {
        //             nodeToDel->parent->left = minChild;
        //         } else {
        //             nodeToDel->parent->right = minChild;
        //         }
        //     }

        //     minChild->parent = nodeToDel->parent;
        //     minChild->left = nodeToDel->left;
        //     minChild->left->parent = minChild;
        //     delete nodeToDel;
        //     }

        // num_pairs--;
        
    }

    // begin()
    // If non-empty, places current iterator at the first (key, value) pair
    // (as defined by the order operator < on keys), otherwise does nothing. 
    void Dictionary::begin() {
        // minimum key value of root
        if(num_pairs <= 0){
        return;
        }
        // move the current location to the first value
        if (this->root != nil) {
            this->current = findMin(root);
        }
    }

    // end()
    // If non-empty, places current iterator at the last (key, value) pair
    // (as defined by the order operator < on keys), otherwise does nothing. 
    void Dictionary::end() {
        // minimum key value of root
        if(num_pairs <= 0){
        return;
        }
        // move the current location to the last value
        if (this->root != nil) {
            this->current = findMax(root);
        }
    }

    // next()
    // If the current iterator is not at the last pair, advances current 
    // to the next pair (as defined by the order operator < on keys). If 
    // the current iterator is at the last pair, makes current undefined.
    // Pre: hasCurrent()
    void Dictionary::next() {
        // check if the current iterator is not nil
        if(!hasCurrent()) {
            throw logic_error("next() Pre: hasCurrent()");
        }
        Node* N = findNext(current);
        if (N == nil) {
            current = nil;
        } else {
            current = N;
        }
    }

    // prev()
    // If the current iterator is not at the first pair, moves current to  
    // the previous pair (as defined by the order operator < on keys). If 
    // the current iterator is at the first pair, makes current undefined.
    // Pre: hasCurrent()
    void Dictionary::prev() {
          // check if the current iterator is not nil
        if(!hasCurrent()) {
            throw logic_error("next() Pre: hasCurrent()");
        }
        Node* N = findPrev(current);
        if (N == nil) {
            current = nil;
        } else {
            current = N;
        }
    }


    // Other Functions ---------------------------------------------------------

    // to_string()
    // Returns a string representation of this Dictionary. Consecutive (key, value)
    // pairs are separated by a newline "\n" character, and the items key and value 
    // are separated by the sequence space-colon-space " : ". The pairs are arranged 
    // in order, as defined by the order operator <.
    std::string Dictionary::to_string() const {
        std::string s = "";
        inOrderString(s, root);
        return s;
    }

    // pre_string()
    // Returns a string consisting of all keys in this Dictionary. Consecutive
    // keys are separated by newline "\n" characters. The key order is given
    // by a pre-order tree walk.
    std::string Dictionary::pre_string() const {
        std::string s = "";
        preOrderString(s, root);
        return s;
    }

    // equals()
    // Returns true if and only if this Dictionary contains the same (key, value)
    // pairs as Dictionary D.
    bool Dictionary::equals(const Dictionary& D) const {
        if(this->num_pairs != D.num_pairs) {
            return false;
        }
        // turn them into string for comparison
        std::string s_this = to_string();
        std::string s_D = D.to_string();
        return s_this == s_D;
    }


// Overloaded Operators ----------------------------------------------------

    // operator<<()
    // Inserts string representation of Dictionary D into stream, as defined by
    // member function to_string().
    std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
        return stream << D.to_string();
    }

    // operator==()
    // Returns true if and only if Dictionary A equals Dictionary B, as defined
    // by member function equals(). 
    bool operator==( const Dictionary& A, const Dictionary& B ) {
        return A.equals(B);
    }

    // operator=()
    // Overwrites the state of this Dictionary with state of D, and returns a
    // reference to this Dictionary.
    Dictionary& Dictionary::operator=( const Dictionary& D ) {
        if(this != &D ) {
            //Make a copy of D
            Dictionary temp = D;

            //then swap the copy's fields with fields of this;
            std::swap(this->nil, temp.nil);
            std::swap(this->root, temp.root);
            std::swap(this->current, temp.current);
            std::swap(this->num_pairs, temp.num_pairs);
        }
        // return this with the new data installed
        return *this;
    }



