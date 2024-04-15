#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

// Binary tree için düğüm yapısı
struct Node {
    int plateCode;
    string cityName;
    Node* left;
    Node* right;
};

// Yeni bir düğüm oluşturan fonksiyon
Node* createNode(int plateCode, string cityName) {
    Node* newNode = new Node;
    newNode->plateCode = plateCode;
    newNode->cityName = cityName;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

// Düğümü ekleyen fonksiyon
Node* insertNode(Node* root, int plateCode, string cityName) {
    // Eğer binary tree boş ise yeni bir düğüm kökü oluşturur
    if (root == nullptr) {
        return createNode(plateCode, cityName);
    }

    // Aksi halde, ağacın altına yinelemeli olarak devam et
    if (plateCode < root->plateCode) {
        root->left = insertNode(root->left, plateCode, cityName);
    } else if (plateCode > root->plateCode) {
        root->right = insertNode(root->right, plateCode, cityName);
    }

    return root;
}

//  Plaka kodları dizisinden bir binary tree oluşturmak için function
Node* createBinaryTree(int plateCodes[], string cityNames[], int size) {
    Node* root = nullptr;
    for (int i = 0; i < size; i++) {
        root = insertNode(root, plateCodes[i], cityNames[i]);
    }
    return root;
}

// Binary tree nin derinliğini hesaplayan fonksiyon
int calculateDepth(Node* root) {
    if (root == nullptr) {
        return 0;
    }

    int leftDepth = calculateDepth(root->left);
    int rightDepth = calculateDepth(root->right);

    return 1 + max(leftDepth, rightDepth);
}

// Binary tree nin dengeli olup olmadığına karar veren fonksyon
bool isBalanced(Node* root) {
    if (root == nullptr) {
        return true;
    }

    int leftDepth = calculateDepth(root->left);
    int rightDepth = calculateDepth(root->right);

    int diff = abs(leftDepth - rightDepth);

    return (diff <= 1) && isBalanced(root->left) && isBalanced(root->right);
}

// Verilen plaka koduna sahip düğümü aramak için fonksiyon
Node* searchNode(Node* root, int plateCode) {
    if (root == nullptr || root->plateCode == plateCode) {
        return root;
    }

    if (plateCode < root->plateCode) {
        return searchNode(root->left, plateCode);
    } else {
        return searchNode(root->right, plateCode);
    }
}

// Düğümün seviyesini bulan fonksiyon
int findLevel(Node* root, int plateCode, int level) {
    if (root == nullptr) {
        return -1;
    }

    if (root->plateCode == plateCode) {
        return level;
    }

    int leftLevel = findLevel(root->left, plateCode, level + 1);
    if (leftLevel != -1) {
        return leftLevel;
    }

    int rightLevel = findLevel(root->right, plateCode, level + 1);
    return rightLevel;
}

// İkili ağacı preorder olarak ekrana yazdıran fonksyon
void preorderTraversal(Node* root) {
    if (root != nullptr) {
        cout << root->plateCode << " ";
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

//  İkili ağacı inorder olarak ekrana yazdıran fonksyon
void inorderTraversal(Node* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        cout << root->plateCode << " ";
        inorderTraversal(root->right);
    }
}

// İkili ağacı postorder olarak ekrana yazdıran fonksyon
void postorderTraversal(Node* root) {
    if (root != nullptr) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        cout << root->plateCode << " ";
    }
}

int main() {
    const int MAX_SIZE = 81; // Txt dosasında 81 giriş olduğunu tahmin ederekten

    ifstream inputFile("sehir_plaka_kodlari.txt");
    if (!inputFile) {
        cerr << "Error opening the file." << endl;
        return 1;
    }

    int plateCodes[MAX_SIZE];
    string cityNames[MAX_SIZE];
    int count = 0;

    while (!inputFile.eof()) {
        int plateCode;
        string cityName;
        inputFile >> plateCode >> cityName;

        plateCodes[count] = plateCode;
        cityNames[count] = cityName;

        count++;
    }

    inputFile.close();

    Node* root = createBinaryTree(plateCodes, cityNames, count);

    // Görsel gösterim
    cout << "Binary Tree:" << endl;
    cout <<"Binary Tree:  37"<<endl;
    cout<<"           /      \\"<<endl;
    cout<<"          14      69"<<endl;
    cout<<"        /   \\    /   \\"<<endl;
    cout<<"       8    28  57   78"<<endl;
    cout<<"     /  \\  /  \\ /  \\ /  \\"<<endl;
    cout<<"    5  19 25 52 53 60 74 81"<<endl;
    cout<<"                     /      "<<endl;
    cout <<"                   61"<<endl;
    cout << "----------------------------" << endl;
    cout << "Plate Codes" << endl;
    cout << "----------------------------" << endl;
    inorderTraversal(root);
    cout << endl << "----------------------------" << endl;

    // Derinlik ve denge hesapları
    int depth = calculateDepth(root);
    bool balanced = isBalanced(root);

    cout << "Depth: " << depth << endl;
    cout << "Balanced: " << (balanced ? "Yes" : "No") << endl;

    // Plaka kodlarını girdiğimiz yer
    int plateCode1, plateCode2;
    cout << "Enter the first plate code: ";
    cin >> plateCode1;
    cout << "Enter the second plate code: ";
    cin >> plateCode2;

    // Şehirlerin isimini bulup level farkını çıkardığımız yer
    Node* node1 = searchNode(root, plateCode1);
    Node* node2 = searchNode(root, plateCode2);

    if (node1 != nullptr && node2 != nullptr) {
        string city1 = node1->cityName;
        string city2 = node2->cityName;

        int levelDiff = findLevel(root, plateCode1, 0) - findLevel(root, plateCode2, 0);

        cout << "City corresponding to plate code " << plateCode1 << ": " << city1 << endl;
        cout << "City corresponding to plate code " << plateCode2 << ": " << city2 << endl;
        cout << "Level difference: " << levelDiff << endl;
    } else {
        cout << "One or both of the plate codes are not found in the binary tree." << endl;
    }

    // preorder, inorder, ve postorder olarak sıralayıp ekrana yazdıran kısım
    cout << endl << "Binary Tree Sorted:" << endl;
    cout << "----------------------------" << endl;
    cout << "Preorder Traversal: ";
    preorderTraversal(root);
    cout << endl;
    cout << "Inorder Traversal: ";
    inorderTraversal(root);
    cout << endl;
    cout << "Postorder Traversal: ";
    postorderTraversal(root);
    cout << endl;
    cout << "----------------------------" << endl;

    return 0;
}