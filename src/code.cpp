#include <iostream>
#include <string>
#include <stack>
#include <queue>
using namespace std;

// ======================================================
//                DOUBLY CIRCULAR NODE
// ======================================================
struct Patient {
    int patientID;
    string name;
    int severity;
    int arrivalOrder;

    Patient* next;
    Patient* prev;
};

Patient* head = NULL;

// ======================================================
//                     BST NODE
// ======================================================
struct BSTNode {
    int id;
    BSTNode* left;
    BSTNode* right;
};

// ======================================================
//                  CUSTOM STACK NODE
// ======================================================
struct StackNode {
    int data;
    StackNode* next;
};

StackNode* topPtr = NULL;

// ======================================================
//               CREATE PATIENT NODE
// ======================================================
Patient* makePatient(int id, string n, int sev, int order) {

    Patient* temp = new Patient();

    temp->patientID = id;
    temp->name = n;
    temp->severity = sev;
    temp->arrivalOrder = order;

    temp->next = NULL;
    temp->prev = NULL;

    return temp;
}

// ======================================================
//               INSERT AT END
// ======================================================
void insertAtEnd(int id, string n, int sev, int order) {

    Patient* temp = makePatient(id, n, sev, order);

    if (head == NULL) {

        head = temp;

        head->next = head;
        head->prev = head;

        return;
    }

    Patient* tail = head->prev;

    tail->next = temp;
    temp->prev = tail;

    temp->next = head;
    head->prev = temp;
}

// ======================================================
//                    DISPLAY LIST
// ======================================================
void printList() {

    if (head == NULL) {
        cout << "List Empty\n";
        return;
    }

    Patient* temp = head;

    do {

        cout << "P(" 
             << temp->patientID << ","
             << temp->name << ","
             << temp->severity << ")";

        temp = temp->next;

        if (temp != head)
            cout << " <-> ";

    } while (temp != head);

    cout << endl;
}

// ======================================================
//                PART (a) BUBBLE SORT
// ======================================================
void bubbleSortPatients() {

    if (head == NULL)
        return;

    bool swapped;

    int comparisons = 0;
    int swaps = 0;
    int pass = 1;

    cout << "\n===== BUBBLE SORT PASSES =====\n";

    do {

        swapped = false;

        Patient* current = head;

        do {

            Patient* nextNode = current->next;

            if (nextNode == head)
                break;

            comparisons++;

            bool condition =
                (current->severity < nextNode->severity) ||

                (
                    current->severity == nextNode->severity &&
                    current->arrivalOrder > nextNode->arrivalOrder
                );

            if (condition) {

                swap(current->patientID, nextNode->patientID);
                swap(current->name, nextNode->name);
                swap(current->severity, nextNode->severity);
                swap(current->arrivalOrder, nextNode->arrivalOrder);

                swaps++;
                swapped = true;
            }

            current = current->next;

        } while (current != head->prev);

        cout << "After Pass " << pass++ << " : ";
        printList();

    } while (swapped);

    cout << "\nTotal Comparisons = " << comparisons << endl;
    cout << "Total Swaps = " << swaps << endl;
}

// ======================================================
//              PRIORITY QUEUE ENQUEUE
// ======================================================
void enqueuePatient(int id, string n, int sev, int order) {

    Patient* temp = makePatient(id, n, sev, order);

    if (head == NULL) {

        head = temp;
        temp->next = temp;
        temp->prev = temp;

        return;
    }

    // insert at front
    if (
        sev > head->severity ||

        (
            sev == head->severity &&
            order < head->arrivalOrder
        )
    ) {

        Patient* tail = head->prev;

        temp->next = head;
        head->prev = temp;

        temp->prev = tail;
        tail->next = temp;

        head = temp;

        cout << temp->name << " inserted at HEAD.\n";

        return;
    }

    Patient* current = head;

    while (current->next != head) {

        Patient* nxt = current->next;

        bool placeHere =
            (sev > nxt->severity) ||

            (
                sev == nxt->severity &&
                order < nxt->arrivalOrder
            );

        if (placeHere)
            break;

        current = current->next;
    }

    Patient* after = current->next;

    current->next = temp;
    temp->prev = current;

    temp->next = after;
    after->prev = temp;

    cout << temp->name
         << " inserted between "
         << current->name
         << " and "
         << after->name << endl;
}

// ======================================================
//                PRIORITY QUEUE DEQUEUE
// ======================================================
void dequeuePatient() {

    if (head == NULL) {
        cout << "Queue Empty\n";
        return;
    }

    cout << "\nDequeued Patient: "
         << head->name
         << " | Severity = "
         << head->severity
         << " | ArrivalOrder = "
         << head->arrivalOrder
         << endl;

    cout << "Reason: Highest severity gets priority.\n";

    if (head->next == head) {

        delete head;
        head = NULL;

        return;
    }

    Patient* tail = head->prev;
    Patient* temp = head;

    head = head->next;

    tail->next = head;
    head->prev = tail;

    delete temp;
}

// ======================================================
//                  STACK FUNCTIONS
// ======================================================
void pushStack(int value) {

    StackNode* temp = new StackNode();

    temp->data = value;
    temp->next = topPtr;

    topPtr = temp;
}

int popStack() {

    if (topPtr == NULL)
        return -1;

    StackNode* temp = topPtr;

    int value = temp->data;

    topPtr = topPtr->next;

    delete temp;

    return value;
}

bool stackEmpty() {
    return topPtr == NULL;
}

void displayStack() {

    StackNode* temp = topPtr;

    cout << "TOP -> ";

    while (temp != NULL) {

        cout << temp->data;

        temp = temp->next;

        if (temp != NULL)
            cout << " -> ";
    }

    cout << endl;
}

// ======================================================
//         REVERSE STACK USING ONE QUEUE
// ======================================================
void reverseStack() {

    queue<int> q;

    cout << "\n===== REVERSING STACK =====\n";

    while (!stackEmpty()) {

        int val = popStack();

        cout << "Pop " << val
             << " from stack -> enqueue into queue\n";

        q.push(val);
    }

    while (!q.empty()) {

        int val = q.front();
        q.pop();

        cout << "Dequeue " << val
             << " from queue -> push into stack\n";

        pushStack(val);
    }

    cout << "\nReversed ";
    displayStack();
}

// ======================================================
//              INFIX TO POSTFIX
// ======================================================
int precedence(char op) {

    if (op == '*' || op == '/')
        return 2;

    if (op == '+' || op == '-')
        return 1;

    return 0;
}

string convertPostfix(string exp) {

    stack<char> st;
    string result = "";

    cout << "\n===== INFIX TO POSTFIX =====\n";

    for (int i = 0; i < exp.length(); i++) {

        char ch = exp[i];

        if (isalnum(ch)) {

            result += ch;

            cout << ch
                 << " added to output -> "
                 << result << endl;
        }

        else if (ch == '(') {

            st.push(ch);

            cout << "( pushed into stack\n";
        }

        else if (ch == ')') {

            while (!st.empty() && st.top() != '(') {

                result += st.top();

                cout << st.top()
                     << " popped into output -> "
                     << result << endl;

                st.pop();
            }

            st.pop();
        }

        else {

            while (
                !st.empty() &&
                precedence(st.top()) >= precedence(ch)
            ) {

                result += st.top();

                cout << st.top()
                     << " popped into output -> "
                     << result << endl;

                st.pop();
            }

            st.push(ch);

            cout << ch << " pushed into stack\n";
        }
    }

    while (!st.empty()) {

        result += st.top();
        st.pop();
    }

    return result;
}

// ======================================================
//                  BST INSERT
// ======================================================
BSTNode* makeBSTNode(int id) {

    BSTNode* temp = new BSTNode();

    temp->id = id;

    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

BSTNode* insertBST(BSTNode* root, int id) {

    if (root == NULL)
        return makeBSTNode(id);

    if (id < root->id)
        root->left = insertBST(root->left, id);

    else
        root->right = insertBST(root->right, id);

    return root;
}

// ======================================================
//                 BST TRAVERSALS
// ======================================================
void inorder(BSTNode* root) {

    if (!root)
        return;

    inorder(root->left);

    cout << root->id << " ";

    inorder(root->right);
}

void preorder(BSTNode* root) {

    if (!root)
        return;

    cout << root->id << " ";

    preorder(root->left);

    preorder(root->right);
}

void postorder(BSTNode* root) {

    if (!root)
        return;

    postorder(root->left);
    postorder(root->right);

    cout << root->id << " ";
}

// ======================================================
//                  BST DELETE
// ======================================================
BSTNode* minimumNode(BSTNode* node) {

    while (node->left != NULL)
        node = node->left;

    return node;
}

BSTNode* deleteNode(BSTNode* root, int id) {

    if (root == NULL)
        return root;

    if (id < root->id)
        root->left = deleteNode(root->left, id);

    else if (id > root->id)
        root->right = deleteNode(root->right, id);

    else {

        if (root->left == NULL) {

            BSTNode* temp = root->right;

            delete root;

            return temp;
        }

        else if (root->right == NULL) {

            BSTNode* temp = root->left;

            delete root;

            return temp;
        }

        BSTNode* successor = minimumNode(root->right);

        cout << "\nInorder Successor of "
             << id
             << " is "
             << successor->id << endl;

        root->id = successor->id;

        root->right =
            deleteNode(root->right, successor->id);
    }

    return root;
}

// ======================================================
//                 BST HEIGHT
// ======================================================
int treeHeight(BSTNode* root) {

    if (!root)
        return 0;

    return 1 + max(
        treeHeight(root->left),
        treeHeight(root->right)
    );
}

// ======================================================
//                  LEFT ROTATION
// ======================================================
BSTNode* leftRotate(BSTNode* x) {

    BSTNode* y = x->right;
    BSTNode* t2 = y->left;

    y->left = x;
    x->right = t2;

    return y;
}

// ======================================================
//                  RIGHT ROTATION
// ======================================================
BSTNode* rightRotate(BSTNode* y) {

    BSTNode* x = y->left;
    BSTNode* t2 = x->right;

    x->right = y;
    y->left = t2;

    return x;
}

// ======================================================
//               CHECK BALANCE ONCE
// ======================================================
BSTNode* balanceTree(BSTNode* root) {

    int leftH = treeHeight(root->left);
    int rightH = treeHeight(root->right);

    cout << "\nLeft Height = " << leftH << endl;
    cout << "Right Height = " << rightH << endl;

    if (leftH - rightH > 1) {

        cout << "LEFT HEAVY -> RIGHT ROTATION\n";

        return rightRotate(root);
    }

    else if (rightH - leftH > 1) {

        cout << "RIGHT HEAVY -> LEFT ROTATION\n";

        return leftRotate(root);
    }

    cout << "Tree already balanced.\n";

    return root;
}

// ======================================================
//                   MERGE SORT
// ======================================================
void merge(int arr[], int left, int mid, int right) {

    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[20], R[20];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    cout << "Merging: ";

    while (i < n1 && j < n2) {

        cout << "(" << L[i]
             << " vs "
             << R[j] << ") ";

        if (L[i] <= R[j])
            arr[k++] = L[i++];

        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    cout << endl;
}

void mergeSort(int arr[], int left, int right) {

    if (left < right) {

        int mid = (left + right) / 2;

        cout << "Split: ";

        for (int i = left; i <= right; i++)
            cout << arr[i] << " ";

        cout << endl;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// ======================================================
//           SORTED INSERTION OF AYESHA
// ======================================================
void insertSortedPatient(
    int id,
    string n,
    int sev,
    int order
) {

    Patient* temp =
        makePatient(id, n, sev, order);

    cout << "\n===== INSERTING "
         << n
         << " =====\n";

    if (head == NULL) {

        head = temp;

        temp->next = temp;
        temp->prev = temp;

        return;
    }

    Patient* current = head;

    while (
        current->next != head &&

        (
            current->next->severity > sev ||

            (
                current->next->severity == sev &&
                current->next->arrivalOrder < order
            )
        )
    ) {

        current = current->next;
    }

    Patient* after = current->next;

    cout << "Inserted between "
         << current->name
         << " and "
         << after->name << endl;

    cout << "\nPointer Updates:\n";

    cout << "current->next = newNode\n";
    cout << "newNode->prev = current\n";
    cout << "newNode->next = after\n";
    cout << "after->prev = newNode\n";

    current->next = temp;
    temp->prev = current;

    temp->next = after;
    after->prev = temp;
}

// ======================================================
//            FORWARD + BACKWARD TRAVERSAL
// ======================================================
void traverseForward() {

    Patient* temp = head;

    cout << "\nForward Traversal: ";

    do {

        cout << temp->patientID << " ";

        temp = temp->next;

    } while (temp != head);

    cout << endl;
}

void traverseBackward() {

    Patient* temp = head->prev;
    Patient* tail = temp;

    cout << "Backward Traversal: ";

    do {

        cout << temp->patientID << " ";

        temp = temp->prev;

    } while (temp != tail);

    cout << endl;
}

// ======================================================
//              AVERAGE SEVERITY
// ======================================================
void averageSeverity() {

    Patient* temp = head;

    int sum = 0;
    int count = 0;

    do {

        sum += temp->severity;
        count++;

        temp = temp->next;

    } while (temp != head);

    double avg = (double)sum / count;

    cout << "\nAverage Severity = "
         << avg << endl;

    temp = head;

    int above = 0;

    cout << "\nPatients Above Average:\n";

    do {

        if (temp->severity > avg) {

            cout << temp->name
                 << " -> Severity "
                 << temp->severity
                 << endl;

            above++;
        }

        temp = temp->next;

    } while (temp != head);

    cout << "Total Above Average = "
         << above << endl;
}

// ======================================================
//            SELECTION SORT SWAP COUNT
// ======================================================
void selectionSortAnalysis() {

    int sev[] = {4,9,4,7,2,9,5};
    int arr[] = {1,2,3,4,5,6,7};

    int n = 7;
    int swaps = 0;

    for (int i = 0; i < n - 1; i++) {

        int maxIndex = i;

        for (int j = i + 1; j < n; j++) {

            if (
                sev[j] > sev[maxIndex] ||

                (
                    sev[j] == sev[maxIndex] &&
                    arr[j] < arr[maxIndex]
                )
            ) {

                maxIndex = j;
            }
        }

        if (maxIndex != i) {

            swap(sev[i], sev[maxIndex]);
            swap(arr[i], arr[maxIndex]);

            swaps++;
        }
    }

    cout << "\nSelection Sort Swaps = "
         << swaps << endl;
}

// ======================================================
//                       MAIN
// ======================================================
int main() {

    cout << "===== ORIGINAL LIST =====\n";

    insertAtEnd(101,"Ali",4,1);
    insertAtEnd(102,"Sara",9,2);
    insertAtEnd(103,"Usman",4,3);
    insertAtEnd(104,"Hina",7,4);
    insertAtEnd(105,"Bilal",2,5);
    insertAtEnd(106,"Zara",9,6);
    insertAtEnd(107,"Hamza",5,7);

    printList();

    // ==================================================
    // PART A
    // ==================================================

    bubbleSortPatients();

    cout << "\nFinal Sorted List:\n";
    printList();

    // ==================================================
    // PART B
    // ==================================================

    cout << "\n===== PRIORITY QUEUE =====\n";

    dequeuePatient();
    printList();

    enqueuePatient(108,"Nida",9,8);
    printList();

    dequeuePatient();
    printList();

    enqueuePatient(109,"Tariq",10,9);
    printList();

    dequeuePatient();
    printList();

    // ==================================================
    // PART C
    // ==================================================

    cout << "\n===== STACK =====\n";

    Patient* temp = head;

    do {

        pushStack(temp->patientID);

        cout << "Push "
             << temp->patientID
             << " -> ";

        displayStack();

        temp = temp->next;

    } while (temp != head);

    reverseStack();

    string postfix =
        convertPostfix("(A+B)*(C-D)");

    cout << "\nFinal Postfix = "
         << postfix << endl;

    // ==================================================
    // PART D
    // ==================================================

    cout << "\n===== BST =====\n";

    BSTNode* root = NULL;

    // changed insertion order
    int bstValues[] =
    {
        104,
        102,
        106,
        101,
        103,
        105,
        107
    };

    for (int i = 0; i < 7; i++) {

        cout << "Inserted "
             << bstValues[i]
             << endl;

        root =
            insertBST(root, bstValues[i]);
    }

    cout << "\nInorder: ";
    inorder(root);

    cout << "\nPreorder: ";
    preorder(root);

    cout << "\nPostorder: ";
    postorder(root);

    cout << "\n\nDeleting 104...\n";

    root = deleteNode(root,104);

    cout << "\nInorder After Delete: ";
    inorder(root);

    root = balanceTree(root);

    cout << "\nInorder After Rotation: ";
    inorder(root);

    // ==================================================
    // PART E
    // ==================================================

    cout << "\n\n===== MERGE SORT =====\n";

    int arr[] =
    {
        101,
        102,
        103,
        105,
        106,
        107
    };

    mergeSort(arr,0,5);

    cout << "\nSorted Array:\n";

    for (int i = 0; i < 6; i++)
        cout << arr[i] << " ";

    cout << "\n\nBST Inorder is already sorted because of BST property.\n";
    cout << "Merge Sort still performs comparisons even on sorted data.\n";

    // ==================================================
    // PART F
    // ==================================================

    insertSortedPatient(
        110,
        "Ayesha",
        6,
        10
    );

    printList();

    traverseForward();
    traverseBackward();

    averageSeverity();

    // ==================================================
    // PART G
    // ==================================================

    selectionSortAnalysis();

    cout << "\n===== MEMORY ANALYSIS =====\n";

    cout << "Extra memory per node in doubly list = 8 bytes\n";

    cout << "For 1,000,000 patients:\n";

    cout << "8,000,000 bytes extra (~7.63 MB)\n";

    cout << "\nThis tradeoff is justified because prev pointer\n";
    cout << "allows backward traversal and easier deletion.\n";

    cout << "\n===== BOTTLENECK =====\n";

    cout << "Biggest bottleneck = Bubble Sort / linear enqueue\n";

    cout << "Worst Case Complexity = O(n)\n";

    cout << "Better structure = Heap Priority Queue\n";

    cout << "Improved Complexity = O(log n)\n";

    return 0;
}

