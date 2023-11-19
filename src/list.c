/*!
 * \file       list.c
 * \author     Ondřej Ševčík
 * \date       6/2019
 * \brief      Implementing functions of ATD list defined in a header file
 * list.h
 * ****************************************************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/* Includes --------------------------------------------------------------------------------------*/
#include "list.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Private types ---------------------------------------------------------------------------------*/
/* Private macros --------------------------------------------------------------------------------*/
#define UNUSED(x) (void)x

/* Private variables -----------------------------------------------------------------------------*/
/* Private function declarations -----------------------------------------------------------------*/
/* Exported functions definitions ----------------------------------------------------------------*/

void List_Init(List_t *const list)
{
    if(list == NULL)
    {
        return;
    }
    list->active = NULL;
    list->first = NULL;

}

void List_Insert_First(List_t *const list, Data_t data)
{
    if(list == NULL)
    {
        return;
    }

    List_Node_Ptr_t firstNode = myMalloc(sizeof(List_Node_t));
    if(firstNode == NULL)
    {
        return;
    }

    firstNode->data = data;
    firstNode->next = list->first;

    list->first = firstNode;
}
void List_First(List_t *const list)
{
    if(list == NULL)
    {
        return;
    }

    list->active = list->first;
}

bool List_Copy_First(List_t list, Data_t *data)
{
    if(list.first == NULL || data == NULL)
    {
        return false;
    }

    Data_t x = list.first->data;
    *data = x;

    return true;
}

void List_Delete_First(List_t *const list)
{
    if (list == NULL || list->first == NULL)
    {
        return;
    }

    if(list->first == list->active)
    {
        list->active = NULL;
    }

    List_Node_Ptr_t secondNode = list->first;
    list->first = list->first->next;

    myFree(secondNode);
}

void List_Post_Delete(List_t *const list)
{
    if (list == NULL || list->active == NULL || list->active->next == NULL)
    {
        return;
    }

    List_Node_Ptr_t thirdNode = list->active->next->next;
    list->active->next->next = NULL;

    myFree(list->active->next);
    list->active->next = thirdNode;
}

void List_Post_Insert(List_t *const list, Data_t data)
{
    if (list == NULL || list->active == NULL)
    {
        return;
    }

    List_Node_Ptr_t fourthNode = myMalloc(sizeof (List_Node_t));
    if(fourthNode == NULL)
    {
        return;
    }

    fourthNode->data = data;

    fourthNode->next = list->active->next;
    list->active->next = fourthNode;
}

bool List_Copy(List_t list, Data_t *data)
{
    if (list.active == NULL || data == NULL)
    {
        return false;
    }

      Data_t x = list.active->data;
      *data = x;

      return true;
}

void List_Active_Update(const List_t *const list, Data_t data)
{
    if (list == NULL || list->active == NULL)
    {
        return;
    }

    list->active->data = data;
}

void List_Active_Next(List_t *const list)
{
    if (list == NULL || list->active == NULL)
    {
        return;
    }

    list->active = list->active->next;
}

bool List_Is_Active(List_t list)
{
    if (list.active != NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/* Private function definitions ------------------------------------------------------------------*/
