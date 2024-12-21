# Red-Black Tree

1. Every node is either red or black.
2. All Leaf nodes (NIL) are considered black.
3. A red node does not have a red child.
4. Every path from a given node to any of its descendant NIL nodes
   goes through the same number of black nodes.
5. If a node N has exactly one child, the child must be red,
   because if it were black, its NIL descendants would sit at
   a different black depth than N's NIL child, violating requirement 4.


# Equivalent Conditions
1. Every node is either red or black.
2. Root node is always black.
3. All Leaf nodes (NIL) are considered black.
4. All paths starting from a node to any of its leaf nodes have
   the same number of black nodes, excluding leaf nodes.
5. Both descendant child nodes of red node are always black.
   (i.e. red nodes cannot appear consecutively, and
    only black node can be parent of red node.)

# Rules that satisfy the above conditions
1. Root node is always black.
2. new nodes are red.
3. If both parent and uncle are red, only execute 'color filp'.
4. If parent is red, do 'rotate'.


# 삽입

새 노드(N)을 red로 설정한 후, 이진 탐색 트리의 규칙에 따라 리프 위치에 삽입한다.
## 1. N이 루트
   N을 black으로 칠한다.

## 2. N의 부모가 black
   별도의 작업 없이 삽입을 종료.

## 3. N의 부모가 red

### 3.1. N의 삼촌이 red
N의 부모와 삼촌이 모두 red라면, 조부모는 black이다. N의 부모와 삼촌을 black으로 변경하고, 조부모를 red로 바꾼다. (color flip)
조부모가 red로 변했기 때문에 조건 위반 가능성이 생겨, 조부모에 대해 해결 과정을 다시 시작한다.

### 3.2. N의 삼촌이 black
N이 부모늬 안쪽 자손인지, 바깥쪽 자손인지에 따라 처리가 달라진다.

#### 3.2.1. N이 안쪽 자손임
N이 부모의 안쪽 자손이라면 (부모가 조부모의 왼쪽 자손이고 N이 부모의 오른쪽 자식인 경우 등),
부모를 기준으로 회전하여 N을 바깥쪽 자손으로 만든다. 이후 N의 부모를 기준으로 처리한다.

#### 3.2.2. N이 바깥쪽 자손임
N이 부모의 바깥쪽 자손이라면, N의 부모를 black으로, 조부모를 red로 설정하고 (color flip),
조부모를 기준으로 회전을 수행한다.

이로써 트리의 균형이 유지되고, 연속된 red 노드가 없도록 조정된다.