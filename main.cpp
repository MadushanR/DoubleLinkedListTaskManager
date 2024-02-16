#include<iostream>
#include<cstdio>
#include <utility>
/*
 Name : Madushan Rajendran
 Date : 16/02/2024
 Description : This is a task manager implement using Double Linked List
 */

///This is the class for Task object
class Task {
private:
    std::string title;
    std::string description;
    int priority;
    std::string dueDate;
    std::string completed;

public:
    Task(std::string title, std::string description, int priority, std::string dueDate, std::string completed)
            : title(std::move(title)), description(std::move(description)), priority(priority), dueDate(std::move(dueDate)), completed(std::move(completed)) {}

    std::string gettitle() const {
        return title;
    }

    std::string getdescription() const {
        return description;
    }

    int getpriority() const {
        return priority;
    }

    std::string getduedate() const {
        return dueDate;
    }

    std::string getcompleted() const {
        return completed;
    }

    void settitle(const std::string& title) {
        this->title = title;
    }

    void setdescription(const std::string& description) {
        this->description = description;
    }

    void setpriority(int priority) {
        this->priority = priority;
    }

    void setdueDate(const std::string& dueDate) {
        this->dueDate = dueDate;
    }

    void setcompleted(const std::string& completed) {
        this->completed = completed;
    }
};

///This is where double linked list node is created
class node {
public:
    node *prev;
    node *next;
    Task task;

    node(Task task) : task(std::move(task)), prev(nullptr), next(nullptr) {}
};

node *head = nullptr;

///This is where the double linked list is created
class dll {
public:
    dll() = default;

    ///inserts Task into the linked list
    static void insert(Task task) {
        node *newNode = new node(std::move(task));
        if (head == nullptr) {
            head = newNode;
        } else {
            node *temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }
    }

    ///deletes task from linked list
    static void deleting() {
        if (head == nullptr) {
            return;
        }

        std::string title;
        std::cout << "Enter Title" << std::endl;
        std::cin >> title;

        node *ptr = head;
        while (ptr != nullptr && ptr->task.gettitle() != title) {
            ptr = ptr->next;
        }

        if (ptr == nullptr) {
            printf("\nTask not found\n");
            return;
        }

        if (ptr->prev != nullptr) {
            ptr->prev->next = ptr->next;
        } else {
            head = ptr->next;
        }

        if (ptr->next != nullptr) {
            ptr->next->prev = ptr->prev;
        }

        delete ptr;
        printf("\nTask deleted\n");
    }

    ///outputs all tasks
    static void display() {
        node *ptr = head;
        if (ptr == nullptr) {
            printf("List is empty\n");
            return;
        }
        while (ptr != nullptr) {
            std::cout << "Title: " << ptr->task.gettitle() << " | Description: " << ptr->task.getdescription() << " | Priority: " << ptr->task.getpriority() << " | Completed: " << ptr->task.getcompleted() << " | Due date: " << ptr->task.getduedate() << std::endl;
            ptr = ptr->next;
        }
    }

    ///updates whether task is completed or not
    static void update() {
        node *ptr = head;
        int flag = 1;
        std::string completed = "false";
        if (ptr != nullptr) {
            std::string taskname;
            std::cout << "Please enter the Task Title: ";
            std::cin >> taskname;
            while (ptr != nullptr) {
                if (ptr->task.gettitle() == taskname) {

                    std::cout << "Please enter completed(True/False): ";
                    std::cin >> completed;
                    ptr->task.setcompleted(completed);
                    printf("\nTask updated");
                    flag = 0;
                    break;
                }
                ptr = ptr->next;
            }
            if (flag == 1) {
                printf("\nTask not found\n");
            }
        }
    }
};

//The UI for the program
int main() {
    int choice = 0;
    while (choice != 5) {
        printf("\nChoose one option from below\n");
        printf("\n===============================================\n");
        printf("\n1.Insert Task\n2.Delete Task\n3.Update Task\n4.Show all Tasks\n5.Exit\n");
        printf("\nEnter your choice?\n");
        scanf("\n%d", &choice);
        switch (choice) {
            case 1: {
                std::string title, description, duedate;
                int priority;
                std::string completed = "false";
                std::cout << "Enter the title of the task: ";
                std::cin >> title;
                std::cout << "Enter the description of the task: ";
                std::cin >> description;
                std::cout << "Enter the priority of the task in numbers only: ";
                std::cin >> priority;
                std::cout << "Enter the due date of the task(dd/mm/yyyy): ";
                std::cin >> duedate;
                Task task(title, description, priority, duedate, completed);
                dll::insert(task);
                break;
            }
            case 2: {
                dll::display();
                dll::deleting();
                break;
            }
            case 3: {
                dll::display();
                dll::update();
                break;
            }
            case 4:
                dll::display();
                break;
            case 5:
                exit(0);
            default:
                printf("Please enter valid choice..\n");
        }
    }
    return 0;
}
