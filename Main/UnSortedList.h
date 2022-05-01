#pragma once
#define MAXSIZE 10

template <class T>
class UnSortedList
{
private:
	T m_Array[10];		// ����Ʈ
	int m_Length;		// ����Ʈ�� ����� ���ڵ� ��
	int m_CurPointer;	// current pointer
public:
	UnSortedList();		// default constructor
	~UnSortedList();		// default destructor

	void MakeEmpty();	// Make list empty
	int GetLength();	// ���ڵ� �� ��ȯ
	bool IsFull();		// ��� �迭�� ��� ����
	int Add(T data);	// ���ο� ������ �߰�
	void ResetList();	// ���ڵ� ������(current pointer) �ʱ�ȭ
	int GetNextItem(T& data);	// current pointer�� �ϳ� ������Ű�� ���� �ƴϸ� record index�� ���� ���̸� -1�� ����
	bool IsEmpty();		// �迭�� ������� ����
	int Get(T& data);	// Primary key�� �������� �����͸� �˻��ϰ� �ش� �����͸� ������
	int Delete(T data);	// ���� ���ڵ� ����
	int Replace(T data);	// �Էµ� data�� Primary key�� ������ ����� ã�Ƽ� List�� �ش� ����� �Էµ� data�� ġȯ�Ѵ�.


};

template <class T>
UnSortedList<T>::UnSortedList() {
	m_Length = 0; m_CurPointer = -1;


}

template <class T>
UnSortedList<T>::~UnSortedList() {}

template <class T>
void UnSortedList<T>::MakeEmpty() {
	m_Length = 0;
}

template <class T>
int UnSortedList<T>::GetLength() { return m_Length; }

template <class T>
bool UnSortedList<T>::IsFull() {
	if (MAXSIZE <= m_Length) { return true; }
	else { return false; }
}

template <class T>
int UnSortedList<T>::Add(T data) {
	if (!IsFull()) {	// ����Ʈ�� �� ������ ���� �� ���̸� 1 ������Ű�� �� ������ ���� �־��� ������ ����
		m_Array[m_Length] = data;
		m_Length++;
		return 1;	// �߰��� �����ϸ� 1�� return
	}
	else
		return 0;	// �߰��� �����ϸ� 0�� return
}

template <class T>
void UnSortedList<T>::ResetList() {
	m_CurPointer = -1;
}
template <class T>
int UnSortedList<T>::GetNextItem(T& data) {
	m_CurPointer++;
	if (m_CurPointer == MAXSIZE)
		return -1;
	data = m_Array[m_CurPointer];

	return m_CurPointer;
}
template <class T>
bool UnSortedList<T>::IsEmpty() {
	if (m_Length == 0) return 1;
	return 0;
}

template <class T>
int UnSortedList<T>::Get(T& data) {
	int i = 0;
	for (int i = 0; i < m_Length; i++) {
		if (m_Array[i]==data) {
			data = m_Array[i];
			return i;
		}
	}

	return -1;

}
template <class T>
int UnSortedList<T>::Delete(T data) {
	int i = Get(data);
	if (i == 0)
		return 0;
	for (int j = i + 1; j < m_Length; j++)
		m_Array[j - 1] = m_Array[j];
	m_Length -= 1;
	return 1;

}

template <class T>
int UnSortedList<T>::Replace(T data) {
	T indata = data;
	int i = Get(indata);
	if (i != -1) {
		m_Array[i] = data;
		return 1;
	}
	return 0;
}