#pragma once
#define MAXSIZE 10

template <class T>
class UnSortedList
{
private:
	T m_Array[10];		// 리스트
	int m_Length;		// 리스트에 저장된 레코드 수
	int m_CurPointer;	// current pointer
public:
	UnSortedList();		// default constructor
	~UnSortedList();		// default destructor

	void MakeEmpty();	// Make list empty
	int GetLength();	// 레코드 수 반환
	bool IsFull();		// 모든 배열의 사용 여부
	int Add(T data);	// 새로운 데이터 추가
	void ResetList();	// 레코드 포인터(current pointer) 초기화
	int GetNextItem(T& data);	// current pointer를 하나 증가시키고 끝이 아니면 record index를 리턴 끝이면 -1을 리턴
	bool IsEmpty();		// 배열이 비었는지 여부
	int Get(T& data);	// Primary key를 기준으로 데이터를 검색하고 해당 데이터를 가져옴
	int Delete(T data);	// 기존 레코드 삭제
	int Replace(T data);	// 입력된 data와 Primary key와 동일한 기록을 찾아서 List의 해당 기록을 입력된 data로 치환한다.


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
	if (!IsFull()) {	// 리스트가 꽉 차있지 않을 때 길이를 1 증가시키고 맨 마지막 값을 주어진 값으로 설정
		m_Array[m_Length] = data;
		m_Length++;
		return 1;	// 추가에 성공하면 1을 return
	}
	else
		return 0;	// 추가에 실패하면 0을 return
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