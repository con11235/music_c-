#pragma once
#include "stdafx.h"
#include<iostream>
#define MAXSIZE 30

template <class T>
class SortedList
{
private:
	T m_Array[MAXSIZE];			// ����Ʈ
	int m_Length;		// ����Ʈ�� ����� ���ڵ� ��
	int m_CurPointer;	// current pointer
public:
	SortedList();		// default constructor
	~SortedList();		// default destructor

	void MakeEmpty();	// Make list empty
	int GetLength();	// ���ڵ� �� ��ȯ
	bool IsEmpty();		// �迭�� ������� ����
	bool IsFull();		// ��� �迭�� ��� ����


	int Add(T data);	// ���ο� ������ �߰�
	void ResetPointer();	// ���ڵ� ������(current pointer) �ʱ�ȭ
	int GetNextItem(T& data);	// current pointer�� �ϳ� ������Ű�� ���� �ƴϸ� record index�� ���� ���̸� -1�� ����
	
	int Get(T& data);	// Primary key�� �������� �����͸� �˻��ϰ� �ش� �����͸� ������
	int Delete(T data);	// ���� ���ڵ� ����
	int DeleteIndex(int idx);
	int Replace(T data);	// �Էµ� data�� Primary key�� ������ ����� ã�Ƽ� List�� �ش� ����� �Էµ� data�� ġȯ�Ѵ�.

	T at(int idx);

	void operator = (SortedList<T> &item);
};


template <class T>
SortedList<T>::SortedList() {
	m_Length = 0; m_CurPointer = -1;
}


template <class T>
SortedList<T>::~SortedList() {}


template <class T>
void SortedList<T>::MakeEmpty() {
	m_Length = 0;
}


template <class T>
int SortedList<T>::GetLength() { return m_Length; }


template <class T>
bool SortedList<T>::IsEmpty() {
	if (m_Length == 0) return 1;
	return 0;
}


template <class T>
bool SortedList<T>::IsFull() {
	if (MAXSIZE <= m_Length) { return true; }
	return false;
}


template <class T>
int SortedList<T>::Add(T data) {
	if (IsEmpty()) {
		m_Array[0] = data;
		m_Length++;
		return 0;
	}
	else if (IsFull()) {
		return -1;
	}
	else if (m_Array[m_Length - 1] < data) {
		m_Array[m_Length] = data;
		m_Length++;
		return m_Length-1;
	}
	else {
		for (int i = 0; i < m_Length; i++) {
			if (m_Array[i]==data) {
				return -1;
			}
			else if (m_Array[i] > data) {
				for (int j = m_Length; i < j; j--)
					m_Array[j] = m_Array[j - 1];
				m_Array[i] = data;
				m_Length++;
				return i;
			}

		}
	}
	return -1;
}


template <class T>
void SortedList<T>::ResetPointer() {
	m_CurPointer = -1;
}


template <class T>
int SortedList<T>::GetNextItem(T& data) {
	m_CurPointer++;
	if (m_CurPointer == m_Length)
		return -1;
	data = m_Array[m_CurPointer];

	return m_CurPointer;
}


template <class T>
int SortedList<T>::Get(T& data) {
	int i = 0;
	for (int i = 0; i < m_Length; i++) {
		if (m_Array[i] == data) {
			data = m_Array[i];
			return i;
		}
		else if (m_Array[i] > data) {
			return -1;
		}
	}

	return -1;

}


template <class T>
int SortedList<T>::Delete(T data) {
	int i = Get(data);
	if (i == -1)
		return 0;
	for (int j = i + 1; j < m_Length; j++)
		m_Array[j - 1] = m_Array[j];
	m_Length -= 1;
	return 1;

}

template <class T>
int SortedList<T>::DeleteIndex(int idx) {
	if (idx < 0 || m_Length <= idx)
		return 0;
	for (int j = idx + 1; j < m_Length; j++)
		m_Array[j - 1] = m_Array[j];
	m_Length -= 1;
	return 1;
}


template <class T>
int SortedList<T>::Replace(T data) {
	T indata = data;
	int i = Get(indata);
	if (i != -1) {
		m_Array[i] = data;
		return i;
	}
	return -1;
}

template <class T>
T SortedList<T>::at(int idx) {
	T item = m_Array[idx];
	return item;
}

template<class T>
void SortedList<T>::operator = (SortedList<T> &item) {
	MakeEmpty();
	item.ResetPointer();
	T data;
	for (int i = 0; i < item.GetLength(); i++) {
		item.GetNextItem(data);
		Add(data);
	}
}