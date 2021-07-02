#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

struct Node
{
    int data;
    Node* pxor; 
};

Node* XOR(Node* a, Node* b)
{
    return (Node*)((int)a^(int)b);
}

void PrintForward(Node* head)
{
    Node* curr = head;
    Node* prev = NULL;
    Node* next;

    if (curr == NULL) printf("NULL");
    while (curr != NULL)
    {
        printf("%d ", curr->data);

        next = XOR(prev, curr->pxor);
        prev = curr;
        curr = next;
    }
    printf("\n");
}

void PrintBackward(Node* tail)
{
    Node* curr = tail;
    Node* prev;
    Node* next = NULL;

    if (curr == NULL) printf("NULL");
    while (curr != NULL)
    {
        printf("%d ", curr->data);

        prev = XOR(next, curr->pxor);
        next = curr;
        curr = prev;
    }
    printf("\n");
}

void Actual(Node* head, Node* act)
{
    if ((act == head) && (act == NULL)) printf("NULL\n");
    else printf("%i\n", act->data);
}
void AddBeg(Node** head, Node** tail, Node** act)
{ 
    int n;
    Node* new_node = (Node*)malloc(sizeof(struct Node));
    scanf("%i", &n);

    new_node->data = n;
    new_node->pxor = *head;

    if (*head != NULL)
    {
        (*head)->pxor = XOR(new_node, (*head)->pxor);
    }
    if (*head == NULL)
    {
        //first insert
        *act = new_node;
        *tail = new_node;
    }
    *head = new_node;
}

Node* Next(Node** act, Node* tail, Node* head)
{
    if (*act == NULL) printf("NULL\n");
    else if(*act == tail) 
        *act = head;
    else
    {
        Node* curr = head;
        Node* prev = NULL;
        Node* next;

        while (curr != *act)
        {
            next = XOR(prev, curr->pxor);
            prev = curr;
            curr = next;
        }
        *act = XOR(prev, (*act)->pxor);
    }
    return *act;
}

Node* Previous(Node** act, Node* tail, Node* head)
{
    if (*act == NULL) printf("NULL\n");
    else if (*act == head) 
        *act = tail;
    else
    {
        Node* curr = head;
        Node* prev = NULL;
        Node* next = NULL;

        while (curr != *act)
        {
            next = XOR(prev, curr->pxor);
            prev = curr;
            curr = next;
        }
        *act = prev;
    }
    return *act;
}

void AddEnd(Node** tail, Node** head, Node** act)
{
    int n;
    Node* new_node = (Node*)malloc(sizeof(struct Node));
    scanf("%i", &n);

    new_node->data = n;
    new_node->pxor = *tail;
    if (*tail == NULL)
    {
        *head = new_node;
        *act = new_node;
    }
    if(*tail != NULL) (*tail)->pxor = XOR((*tail)->pxor, new_node);
    *tail = new_node;
}

void AddAct(Node** act, Node** tail, Node** head)
{
    if ((*act == *head) && (*act != NULL)) 
        AddBeg(head, tail, act);
    else if (*act == NULL) 
        AddBeg(head, tail, act);
    else
    {
        int n;
        Node* new_node = (Node*)malloc(sizeof(Node));
        scanf("%i", &n);

        new_node->data = n;

        Node* curr = *head;
        Node* prev = NULL;
        Node* next = NULL;

        while (XOR(prev, curr->pxor) != *act)
        {
            next = XOR(prev, curr->pxor);
            prev = curr;
            curr = next;
        }

        curr->pxor = XOR(prev, new_node);
        new_node->pxor = XOR(curr, *act);
        (*act)->pxor = XOR(XOR((*act)->pxor, curr), new_node);
        
    }
}

void DelBeg(Node** head, Node** act, Node** tail)
{
    if (*head == NULL);
    else if ((*head)->pxor == NULL)
    {
        free(*head);
        *head = NULL;
        *act = NULL;
        *tail = NULL;
    }
    else
    {
        if (*act == *head) *act = Previous(act, *tail, *head);
        Node* next = (*head)->pxor;
        next->pxor = XOR(*head, next->pxor);
        free(*head);
        *head = next;
    }
}

void DelEnd(Node** head, Node** act, Node** tail)
{
    if (*head == NULL);
    else if ((*head)->pxor == NULL)
    {
        free(*head);
        *head = NULL;
        *act = NULL;
        *tail = NULL;
    }
    else
    {
        if (*act == *tail) *act = Previous(act, *tail, *head);
        Node* prev = (*tail)->pxor;
        prev->pxor = XOR(*tail, prev->pxor);
        free(*tail);
        *tail = prev;
    }
}

void DelAct(Node** head, Node** act, Node** tail)
{
    if ((*act == *head) && (*act != NULL))
        DelBeg(head, act, tail);
    else if ((*act == *tail) && (*act != NULL))
        DelEnd(head, act, tail);
    else if (*act == NULL) 
        return;
    else
    {
        Node* curr = *head;
        Node* prev = NULL;
        Node* next = NULL;

        while (curr != *act)
        {
            next = XOR(prev, curr->pxor);
            prev = curr;
            curr = next;
        }
        next = XOR((*act)->pxor, prev);
        prev->pxor = XOR(XOR(prev->pxor, (*act)), next);
        next->pxor = XOR(XOR(next->pxor, (*act)), prev);
        free(*act);
        *act = prev;
    }
}

void DelVal(Node** head, Node** act, Node** tail)
{
    int val;
    scanf("%i", &val);

    Node* curr = *head;
    Node* prev = NULL;
    Node* next = NULL;

    while (curr != NULL)
    {
        if (curr->data == val)
        {
            if (curr == *head)
            {
                prev = NULL;
                next = curr->pxor;
                if (next == NULL)
                {
                    curr = NULL;
                    DelBeg(head, act, tail);
                }
                else
                {
                    DelBeg(head, act, tail);
                    curr = next;
                }
            
            }
            else if (curr == *tail) 
            {
                next = NULL;
                DelEnd(head, act, tail);
                curr = NULL;
            }
            else if (curr == *act)
            {
                next = XOR(curr->pxor, prev);
                next->pxor = XOR(XOR(curr, next->pxor), prev);
                prev->pxor = XOR(XOR(curr, prev->pxor), next);
                DelAct(head, act, tail);
                curr = next;
            }
            else
            {
                next = XOR(curr->pxor, prev);
                next->pxor = XOR(XOR(curr, next->pxor), prev);
                prev->pxor = XOR(XOR(curr, prev->pxor), next);
                free(curr);
                curr = next;
            }
        }
        else
        {
            next = XOR(prev, curr->pxor);
            prev = curr;
            curr = next;
        }
    }
}

void Free(Node** tail, Node** head, Node** act)
{
    while (*head != NULL)
        DelEnd(head, act, tail);
}

int main()
{
    Node* head = NULL;
    Node* act = head;
    Node* tail = head;

    char command[256];
    while (scanf("%s", command) != EOF)
    {
        if (strcmp(command, "ACTUAL") == 0)
        {
            Actual(head, act);
        }
        else if (strcmp(command, "NEXT") == 0)
        {
            if(act == NULL) printf("NULL\n");
            else printf("%i\n", Next(&act, tail, head)->data);
        }
        else if (strcmp(command, "PREV") == 0)
        {
            if (act == NULL) printf("NULL\n");
            else printf("%i\n", Previous(&act, tail, head)->data);
        }
        else if (strcmp(command, "ADD_BEG") == 0)
        {
            AddBeg(&head, &tail, &act);
        }
        else if (strcmp(command, "ADD_END") == 0)
        {
            AddEnd(&tail, &head, &act);
        }
        else if (strcmp(command, "ADD_ACT") == 0)
        {            
            AddAct(&act, &tail, &head);
        }
        else if (strcmp(command, "DEL_BEG") == 0)
        {
            DelBeg(&head, &act, &tail);
        }
        else if (strcmp(command, "DEL_END") == 0)
        {
            DelEnd(&head, &act, &tail);
        }
        else if (strcmp(command, "DEL_VAL") == 0)
        {
            DelVal(&head, &act, &tail);
        }
        else if (strcmp(command, "DEL_ACT") == 0)
        {
            DelAct(&head, &act, &tail);
        }
        else if (strcmp(command, "PRINT_FORWARD") == 0)
        {
            PrintForward(head);
        }
        else if (strcmp(command, "PRINT_BACKWARD") == 0)
        {
            PrintBackward(tail);
        }
        else printf("Couldn't recognized the command!\n");
    }
    Free(&tail, &head, &act);
}