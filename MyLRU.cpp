#define OLDLIST 0
#define NEWLIST 1
#define MIDPOINT (double)5 / (double)8

#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class LRUList {

private:
  list<int> _newList;
  list<int> _oldList;
  unordered_map<int, pair<list<int>::iterator, int>> _pageMap;
  double midPoint = MIDPOINT;

  // 페이지 존재여부
  bool _existPage(int pageNumber) {
    return _pageMap.find(pageNumber) != _pageMap.end();
  }

  void _balanceList() {
    // 만약 newList크기 / oldList크기가 5/8보다 크다면 조정
    if ((double)_newList.size() / (double)_oldList.size() > midPoint) {
      int num = _newList.back();
      _newList.pop_back();
      _oldList.push_front(num);
    }
  }
  void _printNewList() {
    cout << "NewList 출력" << endl;
    for (int pageNumber : _newList)
      cout << pageNumber << " ";
    cout << endl;
  }
  void _printOldList() {
    cout << "OldList 출력" << endl;
    for (int pageNumber : _oldList)
      cout << pageNumber << " ";
    cout << endl;
  }

public:
  LRUList() {}

  // 페이지 푸시
  void push(int pageNumber) {
    // 페이지가 리스트에 이미 있다면
    if (_existPage(pageNumber)) {
      // 해당 페이지를 newList의 head로 올림
      auto it = _pageMap.find(pageNumber);
      if (it->second.second == OLDLIST)
        _oldList.erase(it->second.first);
      else
        _newList.erase(it->second.first);
      _newList.push_front(pageNumber);
      // map에 페이지숫자와 리스트의 위치, 리스트의 종류를 매핑시킨다.
      _pageMap[pageNumber] =
          pair<list<int>::iterator, int>(_newList.begin(), NEWLIST);
      // newList가 과다해진 상황에 대비해 oldList newList 균형 맞춤
      _balanceList();
      return;
    }
    // 페이지가 리스트에 없는 경우
    // oldList에 추가
    _oldList.push_front(pageNumber);
    // map에 페이지숫자와 리스트의 위치, 리스트의 종류를 매핑시킨다.
    _pageMap[pageNumber] =
        pair<list<int>::iterator, int>(_oldList.begin(), OLDLIST);
  }

  // LRU 리스트 상태 표시
  void print() {
    _printNewList();
    _printOldList();
  }
};

void pushAndPrint(LRUList &lru, int pageNumber) {
  cout << "insert " << pageNumber << endl;
  lru.push(pageNumber);
  lru.print();
  cout << endl;
}

int main() {
  LRUList lru;
  for (int i = 0; i < 8; i++)
    pushAndPrint(lru, i);
  pushAndPrint(lru, 3);
  pushAndPrint(lru, 4);
  pushAndPrint(lru, 5);
  pushAndPrint(lru, 3);
  pushAndPrint(lru, 5);
  pushAndPrint(lru, 3);
}