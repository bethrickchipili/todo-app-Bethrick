#include<iostream>
#include<vector>
#include<fstream>
#include<string>
using namespace std;
void show_menu();


struct Task{
    int id;
    string description;
    bool completed;
};

class Todolist{
    private:
        vector<Task> tasks;
        int nextId;

        void saveToFile(){
            ofstream file("tasks.txt");
            for(const auto& task : tasks){
                file << task.id <<"," << task.description <<"," << task.completed<<endl;
            }
            file.close();
        }

        void loadFromFile(){
            ifstream file("tasks.txt");
            if(!file.is_open())return;

            tasks.clear();
            string line;
            while(getline(file, line)){
                size_t pos1 = line.find(',');
                size_t pos2 = line.find(',', pos1 + 1);

                if(pos1 != string::npos && pos2 !=string ::npos){
                    Task task;
                    task.id = std::stoi(line.substr(0,pos1));
                    task.description = line.substr(pos1 + 1, pos2 - pos1 - 1);
                    task.completed = stoi(line.substr(pos2 + 1));
                    tasks.push_back(task);

                    if(task.id>=nextId){
                        nextId = task.id + 1;
                    }
                }
            }
            file.close();
        }

public:
        Todolist() : nextId(1){
            loadFromFile();
        }

        void addtask(const string& description){
            Task newTask;
            newTask.id = nextId++;
            newTask.description = description;
            newTask.completed = false;
            tasks.push_back(newTask);
            saveToFile();
            cout<<"Task added successfully!"<<endl;
        }

        void viewTasks(){
            if(tasks.empty()){
                cout<<"No tasks found.\n";
                return;
            }
            cout<<"\n--- your Tasks -----\n";
            for(const auto& task:tasks){
                cout<<task.id<<"."<<task.description
                        <<" [" <<(task.completed? "Completed": "Pending") << "]\n";
            };
            cout<<" ----------------------------\n";
        }

        void markComplete(int taskId){
            for(auto& task: tasks){
                if(task.id == taskId){
                    task.completed = true;
                    saveToFile();
                    cout<<"Task marked as complete!\n";
                    return;
                }
            }
            cout<<"Task not found!\n";
        }
        void deleteTask(int taskId){
            for(auto it=tasks.begin(); it !=tasks.end(); ++it){
                if(it->id == taskId){
                    tasks.erase(it);
                    saveToFile();
                    cout<<"Task deleted successfully!\n";
                    return;
                }
            }
            cout<<"Task not found.\n";
        }
};

    void show_menu(){
    cout<<"====================================================="<<endl;
    cout<<"                     TO DO LIST                      "<<endl;
    cout<<"====================================================="<<endl;
    cout<<"1. Add task"<<endl;
    cout<<"2. View tasks"<<endl;
    cout<<"3. Mark task as complete"<<endl;
    cout<<"4. Delete task"<<endl;
    cout<<"5. Exit"<<endl;

    cout<<"Please enter your choice"<<endl;
    
}




int main(){
    Todolist todo;
    int choice;

    do{
        show_menu();
        cin >> choice;
        cin.ignore();

        switch(choice){
            case 1: {
                string description;
                cout<< "Enter task description: ";
                getline(cin, description);
                todo.addtask(description);
                break;
            }
            case 2:
                todo.viewTasks();
                break;
            case 3: {
                int taskId;
                cout<<"Enter task ID to mark complete: ";
                cin>> taskId;
                todo.markComplete(taskId);
                break;
            }
            case 4: {
                int taskId;
                cout<< "Enter task ID to delete: ";
                cin >> taskId;
                todo.deleteTask(taskId);
                break;
            }
            case 5: 
                cout<<"Goodbye! \n";
                break;
            default:
                cout<<"Invalid Choice. Please try again.\n";
        }
    }while(choice!=5);
    

    return 0;

}
