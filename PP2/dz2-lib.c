#include <stdlib.h>
#include <stdio.h>

typedef struct allocationNode {
	void *address;
	size_t size;
	struct allocationNode *next;
} AllocationNode;

AllocationNode *head = NULL,
			   *tail = NULL;

void addNewAllocationNode ( void *address, size_t size ) {
	AllocationNode *newNode = ( AllocationNode* ) malloc ( sizeof ( AllocationNode ) );  

	newNode->address = address;
	newNode->size    = size;
	newNode->next	 = NULL;

	if ( head == NULL ) {
		head = tail = newNode;
	} else {
		tail->next = newNode;
		tail       = newNode;
	}
}

int updateAllocationNode ( void *oldAddress, void *newAddress, size_t newSize ) {
    int updated = 0;
	AllocationNode *current = head;

	while ( current != NULL ) {
		if ( current->address == oldAddress ) {
			break;
		} else {
			current = current->next;
		}
	}

	if ( current != NULL ) {
		current->address = newAddress;
		current->size    = newSize;
		updated          = 1;
	}
    
    return updated;
}

void *m_malloc ( size_t size ) {
	void *p = malloc ( size );

	if ( p != NULL ) {
		addNewAllocationNode ( p, size );
	}

	return p;
}

void *m_calloc ( size_t numberOfItems, size_t size ) { 
	void *p = calloc ( numberOfItems, size );

	if ( p != NULL ) {
		addNewAllocationNode ( p, numberOfItems * size );
	}

	return p;
}

void *m_realloc ( void *address, size_t newSize ) {
	void *p = realloc ( address, newSize );

	if ( p != NULL ) {
		if ( updateAllocationNode ( address, p, newSize ) == 0 ) {
		    addNewAllocationNode ( p, newSize );
		}
	}

	return p;
}

void m_free ( void *address ) {
	AllocationNode *current  = head,
				   *previous = NULL;

	while ( current != NULL ) {
		if ( current->address == address ) {
			AllocationNode *old = current;
			current             = current->next;

			if ( previous == NULL ) {
				head = current;
			} else {
				if ( old == tail ) {
					tail = previous;
				}

				previous->next = current;
			}

			free ( old );
		} else {
			previous = current;
			current  = current->next;
		}
	}
}

void memoryLeakCheck ( ) {
    int memoryLeak = 0;
    
	if ( head != NULL ) {
		while ( head != NULL ) {
			AllocationNode *old = head;

			if ( head->size != 0 ) {
			    memoryLeak = 1;
			}
			
			head = head->next;

			free ( old );
		}
	}
	
	if ( memoryLeak == 1 ) {
        printf ( "\nMEMORY LEAK" );
	}
}



size_t getSizeOfBlock ( void *address ) {
    AllocationNode *current = head;
    
    while ( current != NULL ) {
        if ( current->address == address ) {
            break;
        } else {
            current = current->next;
        }
    }
    
    return current != NULL ? current->size : -1;
}

