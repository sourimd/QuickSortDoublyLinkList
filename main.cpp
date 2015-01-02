#include <iostream>

class Node{
private:
	Node * prev;
	int value;
	Node * next;
public:
	int getValue(){ return value; }
	Node * getPrev(){ return prev; }
	Node * getNext(){ return next; }

	void setValue(int v){ value = v; }
	void setPrev(Node * n){ prev = n; }
	void setNext(Node * n){ next = n; }

	Node(int v):prev(NULL), value(v), next(NULL){}
	~Node(){ delete prev; delete next; }
};

void insert(Node ** st, int v){
	if( *st == NULL ){
		*st = new Node(v);
	}
	else{
		Node * p = *st;
		while( p->getNext() != NULL ){
			p=p->getNext();
		}
		Node * newNode = new Node(v);
		p->setNext( newNode );
		newNode->setPrev( p );
	}
}

Node * getEndNode(Node ** st){
	Node * p = *st;
	while(p->getNext() != NULL){
		p=p->getNext();
	}
	return p;
}

void display( Node ** st){
	Node * p = *st;
	while( p!= NULL){
		std::cout << p->getValue() << "->";
		p=p->getNext();
	}
	std::cout << "NULL" << std::endl;
}

void quickSort( Node ** start, Node ** end){
	//std::cout << "Start-> " << (*start)->getValue() << " End-> " << (*end)->getValue() << std::endl;
	if( *start == *end ){
		return;
	}
	else{
		Node * pivot = *start;
		Node * p = pivot->getNext();
		Node * theOnePreviousToStart;
		Node * theOneNextToEnd;
		Node * temp;
		while( p!= *end ){
			if( p->getValue() < pivot->getValue() ){
				temp = p;
				p->getPrev()->setNext( p->getNext() );
				p->getNext()->setPrev( p->getPrev() );
				p = p->getNext();

				theOnePreviousToStart = (*start)->getPrev();

				temp->setNext( *start );
				temp->setPrev( (*start)->getPrev() );
				if( theOnePreviousToStart != NULL){
					theOnePreviousToStart->setNext( temp );
				}
				
				(*start)->setPrev( temp );
				
				*start = temp;
			}
			else{
				p = p->getNext();
			}
		}
		if( p->getValue() < pivot->getValue() ){
			temp = p;
			theOneNextToEnd = p->getNext();

			p->getPrev()->setNext( p->getNext() );
			if( theOneNextToEnd != NULL ){
				theOneNextToEnd->setPrev( p->getPrev() );
			}
			*end = p->getPrev();

			theOnePreviousToStart = (*start)->getPrev();

			temp->setNext( *start );
			temp->setPrev( (*start)->getPrev() );
			if( theOnePreviousToStart != NULL){
				theOnePreviousToStart->setNext( temp );
			}
			
			(*start)->setPrev( temp );
			
			*start = temp;

		}

		Node * firstHalfEnd = pivot->getPrev();
		Node * dummyStart = *start;
		if( *start != pivot){
			quickSort( &dummyStart, &firstHalfEnd);
		}
		
		Node * secondHalfStart = pivot->getNext();
		Node * dummyEnd = *end;
		if( *end != pivot){
			quickSort( &secondHalfStart, &dummyEnd);
		}
		
	}
}

int main(){
	Node * startNode = NULL;

	insert(&startNode, 34);
	insert(&startNode, 12);
	insert(&startNode, 71);
	insert(&startNode, 21);
	insert(&startNode, 25);
	insert(&startNode, 56);
	insert(&startNode, 85);
	insert(&startNode, 92);
	insert(&startNode, 43);
	insert(&startNode, 87);
	insert(&startNode, 55);
	insert(&startNode, 11);
	insert(&startNode, 90);
	insert(&startNode, 8);
	insert(&startNode, 57);
	insert(&startNode, 84);
	insert(&startNode, 3);

	display(&startNode);

	Node * endNode = getEndNode( &startNode );

	quickSort( &startNode, &endNode );
	display(&startNode);
}