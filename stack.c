/* This file is part of project.

    project is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    project is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with project.  If not, see <http://www.gnu.org/licenses/>.*/


#include "stack.h"
#include <stdlib.h>
void init(stack *s) {
	s->head = NULL;
	s->tail = NULL;
}
void push(stack *s, board b) {
	node * temp;
	temp = (node *)malloc (sizeof(node));
	temp->b = b;
	temp->next = NULL;
	if (s->head == NULL) {
		s->head = temp;
		s->tail = temp;
	}
	else {
		s->tail->next = temp;
		s->tail = s->tail->next;
	}
}
/* the caller must check for empty before calling */
board pop(stack *s) {
	board b;
	node * temp;
	temp = s->head;
	b = s->tail->b;
	if(temp == s->tail) {
		free(temp);
		s->head = NULL;
		s->tail = NULL;
		return b;
	}
	while(temp->next != s->tail)
		temp = temp->next;
	free(s->tail);
	s->tail = temp;
	s->tail->next = NULL;	
	return b;
}
int empty(stack *s) {
	return s->head == NULL;
}
