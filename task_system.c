
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treenode *tree_ptr;
struct treenode
{
int ID;
char Name[20];
char Date[20];
float duration;
int performed_task;
tree_ptr left;
tree_ptr right;
};
typedef tree_ptr BST;

BST find (BST T,int id){
if (T==NULL){
 return NULL;
}
if(id<T->ID){
 return(find(T->left,id));}

 else if (id> T->ID){
   return(find(T->right,id));
 }

 else{
  return T ;
 }

}
////////////////////////////////////////////////////////////////////////////
BST insertion (BST T,int id,char name[],char date[],float duration){
if(T==NULL){//tree is empty
T=(BST)malloc(sizeof(struct treenode));//
if(T==NULL){
   printf("out of space...!\n");
   exit (1);
}
else {

   T->ID =id;
   strcpy(T->Name,name);
   T->Name[strcspn(T->Name, "\n")] = '\0';
   strcpy(T->Date,date);
   T->Date[strcspn(T->Date, "\n")] = '\0'; 
   T->duration=duration;
   T->performed_task = 0;
   T->left = T->right = NULL;}
}
else {
   if (find(T,id)==NULL){

      if (id<T->ID){
      T->left = insertion ( T->left ,id,name,date,duration);
                   }
      else{
      T->right = insertion ( T->right ,id,name,date,duration);
          }


                      }
   else{
   printf("Task with ID %d already exists.", id);
       }
}
return T;
}
///////////////////////////////////////////////////////////////////////////////
BST LoadTasksFile(BST T) {
    FILE *file = fopen("tasks.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return T;
    }

        char k[300];
        while (fgets(k, sizeof(k), file)) {
        int ID ;
        char Name[20] ;
        char Date[20];
        float Duration ;

        char *token = strtok(k, "#");
        if (token == NULL){
        continue;
        }
        ID = atoi(token);

        token = strtok(NULL, "#");
        if (token == NULL){
        continue;
        }
        strncpy(Name, token, sizeof(Name)-1);
        Name[strcspn(Name, "\n")] = '\0';
        token = strtok(NULL, "#");
        if (token == NULL){
        continue;
        }
        strncpy(Date, token, sizeof(Date)-1);
        Date[strcspn(Date, "\n")] = '\0';
        token = strtok(NULL, "#");
        if (token == NULL){
        continue;
        }
        Duration = atof(token);

        T = insertion(T, ID, Name, Date, Duration);

            }

    fclose(file);
    printf("Tasks loaded successfully.\n");
    return T;
}////////////////////////////////////////////////////////////////////////////////

tree_ptr find_min( BST T){

    if ( T == NULL )
    return NULL;
    else
    if ( T->left == NULL )
    return ( T );
    else
    return ( find_min ( T->left ));
}
//////////////////////////////////////////////////////
BST deleteTask( BST T, int id)
    {
    tree_ptr tmp_cell, child;
    if ( T == NULL ){
    printf(" Element not found...!\n");
    }
    else if ( id< T->ID){
    T->left = deleteTask(T->left, id);
    }

    else if ( id > T->ID){
    T->right = deleteTask(T->right, id);
    }

    else if ( T->left && T->right ){  //found ID and has right ,left elements
        tmp_cell = find_min(T->right);
        T->ID = tmp_cell->ID;
        T->right = deleteTask(T->right, T->ID);
       }
    else{
        tmp_cell = T;
        if ( T->left == NULL){
        child = T->right;
        }
        if (T->right == NULL){
        child = T->left;
        }
        free ( tmp_cell);
        return child;
                   }
      return T;
}
//////////////////////////////////////////////////////////////////////////
void search_by_name(BST T,char name[],int *found ){

    if( T==NULL)
    {
    return ;
     }
   search_by_name(T->left, name,found);//left_root_right

    if (strcmp(T->Name, name) == 0) {

        printf("task is found...\n");
        printf("ID: %d\n", T->ID);
        printf("Name: %s\n", T->Name);
        printf("Date: %s\n", T->Date);
        printf("Duration: %.3f\n", T->duration);
        *found=1;}

  search_by_name(T->right, name,found);
}
//////////////////////////////////////////////////////////////////
BST perform_task(BST T, int id) {
    BST task = find(T, id);
    if (T == NULL) {
    printf("Task with ID %d not found!\n",id);
    return T;
    }


    if (task->performed_task == 1) {
        printf("Task with ID: %d was already performed!\n",  task->ID);
    }
    else {
    task->performed_task = 1;
    printf("Successfully marked task of ID: %d as performed task ...\n", task->ID);
    }
    return T;
}
//////////////////////////////////////////////////////////////
void view_unperformed_tasks(BST T) {
    if (T == NULL) {
        return;
    }

    view_unperformed_tasks(T->left);

    if (T->performed_task == 0) {
        printf("_________________________________________________\n");
        printf("Task Name: %s\n", T->Name);
        printf("ID: %d\n", T->ID);
        printf("Date: %s\n", T->Date);
        printf("Duration: %.2f\n", T->duration);
        printf("_________________________________________________\n");

    }

    view_unperformed_tasks(T->right);
}
///////////////////////////////////////////////////////////////////
void view_performed_tasks(BST T) {
    if (T == NULL) {
        return;
    }

    view_performed_tasks(T->left);

    if (T->performed_task == 1) {
        printf("_________________________________________________\n");
        printf("Task Name: %s\n",T->Name);
        printf("ID: %d\n",T->ID);
        printf("Date: %s\n",T->Date);
        printf("Duration: %.2f\n",T->duration);
        printf("_________________________________________________\n");

    }

    view_performed_tasks(T->right);
}//////////////////////////////////////////////////////////////////////
void freeTree(BST T) {
    if (T == NULL) return;

    freeTree(T->left);
    freeTree(T->right);
    free(T);
}
////////////////////////////////////////////////////////////////////////
int compare_name(BST T, BST N) {
    int cmp = strcmp(T->Name, N->Name);
    if (cmp == 0) {
    if (T->ID < N->ID)
    return -1;
    else
    return 1;
    }
    return cmp;
}
int compare_date(BST a, BST b) {
    int cmp = strcmp(a->Date, b->Date);

    if (cmp == 0) {
        if (a->ID < b->ID) {
            return -1;
        } else {
            return 1;
        }
    } else {
        return cmp;
    }
}
int compare_duration(BST a, BST b) {
    if (a->duration < b->duration) {
        return -1;
    } else if (a->duration > b->duration) {
        return 1;
    } else {
        if (a->ID < b->ID) {
            return -1;
        } else {
            return 1;
        }
    }
}

int compare(BST a, BST b,int choice ) {
       switch(choice) {
        case 1:
            {
              return compare_name(a, b);
              break;
            }
        case 2:
            {
                return compare_date(a, b);
                break;

            }
        case 3:
            {
                return compare_duration(a, b);
                break;

            }

           default:{ //�� ���� ��� ��� ���� ������ ��� ����� ������
            return compare_name(a, b);
            }
    }
}


    BST insertToNewTree(BST root,BST node,int choice) {
    if(root==NULL){
    return node;
                  }

    if (compare(node,root,choice)<0){
    root->left = insertToNewTree(root->left, node, choice);
                                    }

    else {
        root->right = insertToNewTree(root->right, node, choice);
        }

        return root;
                                                }
 //////////////////////////////////////////////////////////////////
    BST copyToNewTree(BST oldNode, BST root,int choice) {
    if (oldNode == NULL)
        return root ;

   root= copyToNewTree(oldNode->left,root,choice);

    BST newNode = (BST)malloc(sizeof(struct treenode));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->ID = oldNode->ID;
    strcpy(newNode->Name, oldNode->Name);
    strcpy(newNode->Date, oldNode->Date);
    newNode->duration = oldNode->duration;
    newNode->performed_task = oldNode->performed_task;
    newNode->left = newNode->right = NULL;


    root =insertToNewTree(root,newNode,choice);
    root =copyToNewTree(oldNode->right,root,choice);

    return root;

}
BST restructureByNameThenID(BST T) {
    if (T == NULL) {
        printf("Original tree is empty...!\n");
        return NULL;
    }
    printf("\nChoose attribute to restructure by:\n");
    printf("1: Task Name \n");
    printf("2: Task Date \n");
    printf("3: Task Duration\n");
    printf("Enter your choice (1-3): ");

    int choice;
    scanf("%d", &choice);
    if (choice < 1 || choice > 3) {
        printf("Invalid choice...!\n  Name will be used by default...\n");
        choice = 1;
    }
     BST root = NULL;
     root= copyToNewTree(T, root,choice);
     freeTree(T);

     printf("Tree restructured by: ");
      switch(choice) {
        case 1:{
            printf("Task Name\n");
             break;
             }
        case 2: {
            printf("Task Date\n");
             break;
                }
        case 3:{
            printf("Task Duration\n");
             break;
             }
    }

    return root;
}
/////////////////////////////////////////////////////////////
int treeHeight(BST T ){
if (T==NULL){
  return -1;
}
int leftSide=treeHeight(T->left);
int rightSide=treeHeight(T->right);
if(leftSide>rightSide){
return 1 + leftSide;
}
else{
return 1 + rightSide;
}
}
/////////////////////////////////////////////////////////
int treeSize(BST T) {
    if (T == NULL) {//empty
        return 0;
    }
    int leftSide = treeSize(T->left);
    int rightSide = treeSize(T->right);
    return 1 + leftSide + rightSide;
}
//////////////////////////////////////////////////////
int countLeaves(BST T) {
    if (T == NULL) {
        return 0;
    }
    if (T->left == NULL && T->right == NULL) {
        return 1;
    }
    int leftLeaves = countLeaves(T->left);
    int rightLeaves = countLeaves(T->right);
    int totalLeaves = leftLeaves + rightLeaves;

    return totalLeaves;
}
///////////////////////////////////////////////////
int countInternalNodes(BST T) {
    if (T == NULL || (T->left == NULL && T->right == NULL)) {
        return 0;
    }

    int leftInternal = countInternalNodes(T->left);
    int rightInternal = countInternalNodes(T->right);
    int totalInternal = 1 + leftInternal + rightInternal;

    return totalInternal;
}
///////////////////////////////////////////////////
void displayBSTInfo(BST T) {
    if (T == NULL) {
        printf("The tree is empty.\n");
        return;
    }

    printf("\n BST Information:\n___________________________________________________\n");
    printf("Tree Height: %d\n",treeHeight(T));
    printf("Total Nodes: %d\n",treeSize(T));
    printf("Leaf Nodes: %d\n",countLeaves(T));
    printf("Internal Nodes: %d\n",countInternalNodes(T));

}

int main()
{
    BST T=NULL;
    int choice;
    do {
    printf("\nTask Management System\n");
    printf("1. Load Tasks File\n");
    printf("2. Add a New Task\n");
    printf("3. Delete a Task\n");
    printf("4. Search for a Task\n");
    printf("5. Perform a Task\n");
    printf("6. View Unperformed Tasks\n");
    printf("7. View Performed Tasks\n");
    printf("8. Restructure the Tasks BST\n");
    printf("9. View the tasks BST info\n");
    printf("10. Exit\n");
    printf("Enter choice: ");
    scanf("%d",&choice);

  switch(choice) {
    case 1: {
    T=LoadTasksFile(T);
    break;
    }
    case 2:{
    int ID;
    char Name[50];
    char Date[20];
    float Duration;
    printf("\nEnter Task ID: ");
    scanf("%d",&ID);

    printf("\nEnter Task Name: ");
    getchar();
    fgets(Name, sizeof(Name),stdin);  //stdin:Reading input from keyboard
    printf("\nEnter Task Date(e.g day/month/year): ");
    fgets(Date, sizeof(Date),stdin);
    printf("\nEnter Task Duration: ");
    scanf("%f",&Duration);
   T= insertion(T,ID,Name,Date,Duration);
    break;
}
case 3: {
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);
    T = deleteTask(T,id);
    break;}

  case 4:{
  char name[50];
    printf("Enter name to search: ");
    getchar();
    fgets(name,sizeof(name),stdin);
    name[strcspn(name, "\n")] = '\0';
    int found=0;
    search_by_name(T,name,&found);
    if(found==0){
    printf("Task not found.\n");
    }
   break;
  }

   case 5: {
    int id;
    printf("enter ID of task to mark as performed: ");
    scanf("%d", &id);
    T = perform_task(T,id);
    break;
}
case 6: {
    printf("\nunperformed task(s):\n");
    view_unperformed_tasks(T);
    break;
        }
case 7: {
    printf("\nperformed task(s):\n");
    view_performed_tasks(T);
    break;
        }
case 8: {
    T = restructureByNameThenID(T);
    break;
       }

case 9: {
    displayBSTInfo(T);
    break;
        }
case 10: {
    exit(1);
    break;
        }
  default:{
    printf("Invalid choice! Please try again.\n");
        }
        }
    } while(choice != 10);
  return 0;
}
