#pragma once

#include "DynamicQueue.h"


template<class T, int N>
NTree<T, N>::NTree(const NTree<T, N>& aOtherTree)
{
	fKey = aOtherTree.fKey;
	for (int i = 0; i < N; i++)
	{
		if (aOtherTree.fNodes[i] != &NIL)
		{
			fNodes[i] = new NTree<T, N>( *aOtherTree.fNodes[i] );
		}
		else
		{
			fNodes[i] = &NIL;
		}
	}
}

template<class T, int N>
NTree<T, N>::~NTree()
{
	for (int i = 0; i < N; i++)
	{
		if (fNodes[i] != &NIL)
		{
			delete fNodes[i];
		}
	}
}

template<class T, int N>
NTree<T, N>& NTree<T, N>::operator=( const NTree<T, N>& aOtherNTree) 
{
	if (this != &aOtherNTree) 
	{
		for (int i = 0; i < N; i++)
		{
			if (fNodes[i] != &NIL)
			{
				delete fNodes[i];
			}
		}

		fKey = aOtherNTree.fKey;

		for (int i = 0; i < N; i++)
		{
			if (aOtherNTree.fNodes[i] != &NIL)
			{
				fNodes[i] = new NTree<T, N>(*aOtherNTree.fNodes[i]);
			}
			else 
			{
				fNodes[i] = &NIL;;
			}
		}

	}
	return *this;
}

/*
 *My solution for this Problem Set was based heavily upon my Ai Assignment,
 *that is why i used the name Frontier an currentNode
*/

template<class T, int N>
void NTree<T, N>::traverseBreadthFirst(const TreeVisitor<T>& aVisitor) const
{
	DynamicQueue< const NTree<T, N>*> Frontier;
	if (!isEmpty())
	{
		Frontier.enqueue( this );
	}

	while (!Frontier.isEmpty())
	{
		const NTree<T, N>* currentNode = Frontier.top();
		Frontier.dequeue();

		if (!currentNode->isEmpty())
		{
			aVisitor.visit(currentNode->key());

			for (int i = 0; i < N; i++)
			{
				if (currentNode->fNodes[i] != &NIL)
				{
					Frontier.enqueue((const NTree<T, N>*)currentNode->fNodes[i]);
				}
			}


		}
	}
}