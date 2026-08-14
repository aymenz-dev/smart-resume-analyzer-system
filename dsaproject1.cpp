#include <iostream>
#include <string>
using namespace std;

class Resume {
public:
    int id;
    string name;
    string skill;
    int experience;
    int score;
    Resume* next;

    Resume(int i, string n, string sk, int exp) {
        id = i;
        name = n;
        skill = sk;
        experience = exp;

        score = experience * 10;
        if (skill == "C++" || skill == "Python" || skill == "Java")
            score += 20;

        next = NULL;
    }
};

class StackNode {
public:
    Resume data;
    StackNode* next;

    StackNode(Resume r) : data(r) {
        next = NULL;
    }
};

class TreeNode {
public:
    int score;
    string name;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int s, string n) {
        score = s;
        name = n;
        left = right = NULL;
    }
};

class ResumeSystem {
private:
    Resume* head;
    StackNode* top;

public:
    ResumeSystem() {
        head = NULL;
        top = NULL;
    }

    void addResume(int id, string name, string skill, int exp) {
        if (exp < 0) {                          // VALIDATION: negative experience not allowed
            cout << "Invalid Experience\n";
            return;
        }

        Resume* newNode = new Resume(id, name, skill, exp);

        if (head == NULL)
            head = newNode;
        else {
            Resume* temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
        }

        cout << "Resume Added Successfully\n";
    }

    void displayResumes() {
        if (head == NULL) {
            cout << "No Resumes Found\n";
            return;
        }

        Resume* temp = head;

        while (temp != NULL) {
            cout << "\nID: " << temp->id;
            cout << "\nName: " << temp->name;
            cout << "\nSkill: " << temp->skill;
            cout << "\nExperience: " << temp->experience;
            cout << "\nScore: " << temp->score;
            cout << "\n----------------------\n";

            temp = temp->next;
        }
    }

    void searchResume(int id) {
        Resume* temp = head;

        while (temp != NULL) {
            if (temp->id == id) {
                cout << "\nResume Found\n";
                cout << "Name: " << temp->name;
                cout << "\nSkill: " << temp->skill;
                cout << "\nScore: " << temp->score << endl;
                return;
            }
            temp = temp->next;
        }

        cout << "Resume Not Found\n";
    }

    void sortResumes() {
        Resume* i;
        Resume* j;

        for (i = head; i != NULL; i = i->next) {
            Resume* minNode = i;

            for (j = i->next; j != NULL; j = j->next) {
                if (j->score > minNode->score)
                    minNode = j;
            }

            swap(i->id, minNode->id);
            swap(i->name, minNode->name);
            swap(i->skill, minNode->skill);
            swap(i->experience, minNode->experience);
            swap(i->score, minNode->score);
        }

        cout << "Resumes Ranked By Score\n";
    }

    void pushDeleted(Resume r) {
        StackNode* newNode = new StackNode(r);
        newNode->next = top;
        top = newNode;
    }

    void deleteResume(int id) {
        if (head == NULL) return;

        if (head->id == id) {
            pushDeleted(*head);

            Resume* del = head;
            head = head->next;
            delete del;

            cout << "Resume Deleted\n";
            return;
        }

        Resume* temp = head;

        while (temp->next != NULL) {
            if (temp->next->id == id) {
                pushDeleted(*(temp->next));

                Resume* del = temp->next;
                temp->next = temp->next->next;
                delete del;

                cout << "Resume Deleted\n";
                return;
            }
            temp = temp->next;
        }

        cout << "Resume Not Found\n";
    }

    void undoDelete() {
        if (top == NULL) {
            cout << "Nothing To Undo\n";
            return;
        }

        Resume r = top->data;

        addResume(r.id, r.name, r.skill, r.experience);

        StackNode* temp = top;
        top = top->next;
        delete temp;

        cout << "Delete Undone\n";
    }

    TreeNode* insertBST(TreeNode* root, int score, string name) {
        if (root == NULL)
            return new TreeNode(score, name);

        if (score < root->score)
            root->left = insertBST(root->left, score, name);
        else
            root->right = insertBST(root->right, score, name);

        return root;
    }

    TreeNode* buildTree() {
        TreeNode* root = NULL;

        Resume* temp = head;

        while (temp != NULL) {
            root = insertBST(root, temp->score, temp->name);
            temp = temp->next;
        }

        return root;
    }

    void inorder(TreeNode* root) {
        if (root != NULL) {
            inorder(root->right);
            cout << root->name << "  Score: " << root->score << endl;
            inorder(root->left);
        }
    }

    void showRanking() {
        TreeNode* root = buildTree();

        cout << "\n----- Candidate Ranking -----\n";
        inorder(root);
    }
};

int main() {
    ResumeSystem rs;

    int choice, id, exp;
    string name, skill;

    do {
        cout << "\n\n===== SMART RESUME ANALYZER =====\n";
        cout << "1. Add Resume\n";
        cout << "2. Display Resumes\n";
        cout << "3. Search Resume\n";
        cout << "4. Sort / Rank Resumes\n";
        cout << "5. Delete Resume\n";
        cout << "6. Undo Delete\n";
        cout << "7. Show BST Ranking\n";
        cout << "8. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter ID: ";
            cin >> id;

            cout << "Enter Name: ";
            cin >> name;

            cout << "Enter Skill: ";
            cin >> skill;

            cout << "Enter Experience: ";
            cin >> exp;

            rs.addResume(id, name, skill, exp);
            break;

        case 2:
            rs.displayResumes();
            break;

        case 3:
            cout << "Enter ID: ";
            cin >> id;
            rs.searchResume(id);
            break;

        case 4:
            rs.sortResumes();
            break;

        case 5:
            cout << "Enter ID To Delete: ";
            cin >> id;
            rs.deleteResume(id);
            break;

        case 6:
            rs.undoDelete();
            break;

        case 7:
            rs.showRanking();
            break;
        }

    } while (choice != 8);

    return 0;
}