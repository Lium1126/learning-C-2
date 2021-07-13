List *add_member(List *root, int num) {
  List *current = root;  // 今見ている要素
  List *prev = NULL;     // 今見ている要素の前の要素

  while (current != NULL && num < current -> num) {
    prev = current;
    current = current -> next;
  }

  List *p = (List*)malloc(sizeof(List));
  p -> num = num;
  p -> next = NULL;

  if (prev == NULL) {   // 挿入位置が先頭
    p -> next = root;
    return(p);
  } else {              // 挿入位置が先頭以外
    prev -> next = p;
    p -> next = current;
    return(root);  // 先頭を返す
  }
}

List *delete_member(List *root, int delnum) {
  List *current = root;  // 今見ている要素
  List *prev = NULL;     // 今見ている要素の前の要素

  while (current != NULL) {
    if (current -> num == delnum) {
      break;
    }
    prev = current;
    current = current -> next;
  }

  if (current == NULL) {  // 削除する要素がない
    return(root);
  } else if (prev == NULL) {  // 削除する要素は先頭要素
    free(current);
    return(current -> next);
  } else {  // 削除する要素は先頭でない
    prev -> next = current -> next;
    free(current);
    return(root);
  }
}
