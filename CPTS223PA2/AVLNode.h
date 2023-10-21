template <class T>
class AVLNode {
public:
    int height;
    AVLNode* pLeft;
    AVLNode* pRight;
    T data;

    AVLNode(T data)
    {
        pLeft = nullptr;
        pRight = nullptr;
        this->data = data;
        height = 0;
    }

    ~AVLNode()
    {
        delete pLeft;
        delete pRight;
    }
};