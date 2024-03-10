#include "skip_list.hh"

#include <sys/types.h>

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <new>  // Include the header file for 'operator new'

SkipList::Node* SkipList::NewNode(const int& key, int height) {
  void* const node_mem = operator new(sizeof(Node) +
                                      sizeof(void*) * (height - 1));
  return new (node_mem) Node(key);
}

int SkipList::RandomHeight() {  // 平均每个节点的高度为1/(1-p)
  int height = 1;
  while (height < kMaxHeight && (rand() % 4) == 0) {
    height++;
  }
  return height;
}

bool SkipList::KeyIsAfterNode(const int& key, Node* node) const {
  return (node != nullptr) && (key > node->key);
}

SkipList::Node* SkipList::FindGreaterOrEqual(const int& key,
                                             Node** prev) const {
  Node* cur_node = head_;
  auto level = GetMaxHeight() - 1;
  while (true) {
    auto next_node = cur_node->Next(level);
    if (KeyIsAfterNode(key, next_node)) {
      cur_node = next_node;
    } else {  // key <= next_node->key
      //说明key在当前层的下一个节点之前，所以要往下一层走
      //记录一下当前节点，如果不需要记录，prev就是nullptr
      if (prev != nullptr) prev[level] = cur_node;
      if (level == 0) {
        return next_node;
      } else {
        level--;
      }
    }
  }
}

SkipList::Node* SkipList::FindLessThan(const int& key) const {
  auto cur_node = head_;
  auto level = GetMaxHeight() - 1;
  while (true) {
    auto next_node = cur_node->Next(level);
    if (next_node != nullptr and next_node->key < key) {
      cur_node = next_node;
    } else {
      if (level == 0) {
        return cur_node;
      } else {
        level--;
      }
    }
  }
  return nullptr;
}
SkipList::Node* SkipList::FindLast() const {
  auto cur_node = head_;
  auto level = GetMaxHeight() - 1;
  while (true) {
    auto next_node = cur_node->Next(level);
    if (next_node) {
      cur_node = next_node;
    } else {
      if (level == 0) {
        return cur_node;
      } else {
        level--;
      }
    }
  }
}

SkipList::SkipList() : head_(NewNode(0, kMaxHeight)), max_height_(1) {
  for (int i = 0; i < kMaxHeight; i++) {
    head_->SetNext(i, nullptr);
  }
}

bool SkipList::Contains(const int key) const {
  Node* node = FindGreaterOrEqual(key, nullptr);
  return (node != nullptr && Equal(key, node->key));
}

void SkipList::Insert(const int key) {
  Node* prev[kMaxHeight];
  Node* cur_node = FindGreaterOrEqual(key, prev);  // 找到要插入的位置

  assert(cur_node == nullptr or !Equal(key, cur_node->key));

  auto height = RandomHeight();   // 随机生成一个高度
  if (height > GetMaxHeight()) {  // 如果高度大于当前最大高度
    for (int i = GetMaxHeight(); i < height; i++) {
      prev[i] = head_;
    }
    max_height_ = height;
  }

  cur_node = NewNode(key, height);
  for (int i = 0; i < height; i++) {  // 插入节点，更新自己的next和prev的next
    cur_node->SetNext(i, prev[i]->Next(i));
    prev[i]->SetNext(i, cur_node);
  }
}
