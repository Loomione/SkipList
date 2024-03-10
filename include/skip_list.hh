#pragma once

class SkipList {
 public:
  struct Node;
  explicit SkipList();
  SkipList(const SkipList&) = delete;
  SkipList& operator=(const SkipList&) = delete;
  void Insert(int key);
  bool Contains(const int key) const;

 private:
  enum { kMaxHeight = 12 };
  /**
   * @brief 获取跳表的最大高度
   *
   * @return int
   */
  inline int GetMaxHeight() const { return max_height_; }
  Node* NewNode(const int& key, int height);
  int RandomHeight();
  bool Equal(const int& a, const int& b) const { return a == b; }
  /**
   * @brief 判断key是否在节点n之后
   *
   * @param key    要判断的key
   * @param n      节点
   * @return true  key在节点n之后
   * @return false key不在节点n之后
   */
  bool KeyIsAfterNode(const int& key, Node* n) const;
  /**
   * @brief 发现大于或等于key的节点
   *
   * @param key
   * @param prev 用来存储查找路径的节点，是一个存放Node*的数组
   * @return Node* 返回大于或等于key的节点
   */
  Node* FindGreaterOrEqual(const int& key, Node** prev) const;
  /**
   * @brief 返回最后一个一个小于key的节点, node->key < key
   *
   * @param key
   * @return Node*
   */
  Node* FindLessThan(const int& key) const;
  Node* FindLast() const;
  Node* const head_;
  int max_height_;
};

struct SkipList::Node {
  explicit Node(int k) : key(k) {}
  int const key;
  /**
   * @brief 返回节点第n层的下一个节点
   *
   * @param n
   * @return Node*
   */
  Node* Next(int n) { return next_[n]; }
  /**
   * @brief 设置节点第n层的下一个节点
   *
   * @param n 层
   * @param x 要设置的节点
   */
  void SetNext(int n, Node* x) { next_[n] = x; }

 private:
  /*比起在结构体中声明一个指针变量、再进行动态分
   * 配的办法，这种方法效率要高。因为在访问数组内容时，不需要间接访问，避免了两次访存。*/
  Node* next_[1];  // A flexible array member, see
                   // https://en.wikipedia.org/wiki/Flexible_array_member
};
