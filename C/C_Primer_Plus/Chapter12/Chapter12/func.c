#include <stdio.h>
#include "func.h"
/*-------------p17_7-------------*/

//************内部函数原型等
typedef struct {
    Node* parent;
    Node* child;
}Pair;
static Node* MakeNode(const Item_word* pi);//
static bool ToLeft(const Item_word* i1, const Item_word* i2);//
static bool ToRight(const Item_word* i1, const Item_word* i2);//
static void AddNode(Node* new_node, Node* root);//
static void InOrder(const Node* root, void (*pfun)(Item_word item));//
static Pair SeekItem(const Item_word* pi, const Tree* ptree);//
static void DeleteNode(Node** ptr);//
static void DeleteAllNodes(Node* ptr);//

//做叶节点
static Node* MakeNode(const Item_word* pi)
{
    Node* new_node;

    new_node = (Node*)malloc(sizeof(Node));
    if (new_node != NULL)
    {
        new_node->item_word = *pi;
        new_node->item_word.count = 1;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    return new_node;
}
static bool ToLeft(const Item_word* i1, const Item_word* i2)//应该放左树
{
    return strcmp(i1->word, i2->word) < 0 ? true : false;
}

static bool ToRight(const Item_word* i1, const Item_word* i2)//应该放右树
{
    return strcmp(i1->word, i2->word) > 0 ? true : false;
}
//将节点加到树上
static void AddNode(Node* new_node, Node* root)//
{
    if (ToLeft(&new_node->item_word, &root->item_word))
    {
        if (root->left == NULL)
        {
            root->left = new_node;
        }
        else
        {
            AddNode(new_node, root->left);
        }
    }
    else if (ToRight(&new_node->item_word, &root->item_word))
    {
        if (root->right == NULL)
        {
            root->right = new_node;
        }
        else
        {
            AddNode(new_node, root->right);
        }
    }
    else
    {
        fprintf(stderr, "Can't add repetitive item!\n");
        exit(EXIT_FAILURE);
    }
    return;
}
//按顺序应用func
static void InOrder(const Node* root, void (*pfun)(Item_word item))//
{
    if (root != NULL)
    {
        InOrder(root->left, pfun);
        (*pfun)(root->item_word);
        InOrder(root->right, pfun);
    }
    return;
}
//找到item的父与子
static Pair SeekItem(const Item_word* pi, const Tree* ptree)
{
    Pair look;
    look.parent = NULL;
    look.child = ptree->root;

    if (look.child == NULL)
    {
        return look;
    }
    while (look.child != NULL)
    {
        if (ToLeft(pi, &(look.child->item_word)))
        {
            look.parent = look.child;
            look.child = look.child->left;
        }
        else if (ToRight(pi, &(look.child->item_word)))
        {
            look.parent = look.child;
            look.child = look.child->right;
        }
        else
        {
            break;
        }
    }
    return look;
}
//删除node
static void DeleteNode(Node** ptr)
{
    Node* temp;

    if ((*ptr)->left == NULL)
    {
        temp = *ptr;
        *ptr = (*ptr)->right;
        free(temp);
    }
    else if ((*ptr)->right == NULL)
    {
        temp = *ptr;
        *ptr = (*ptr)->left;
        free(temp);
    }
    else
    {
        for (temp = (*ptr)->left; temp->right != NULL; temp = temp->right)
        {
            continue;
        }
        temp->right = (*ptr)->right;
        temp = *ptr;
        *ptr = (*ptr)->left;
        free(temp);
    }
    return;
}
//
static void DeleteAllNodes(Node* root)
{
    Node* pright;

    if (root != NULL)
    {
        pright = root->right;
        DeleteAllNodes(root->left);
        free(root);
        DeleteAllNodes(pright);
    }
    return;
}







//***************接口函数原型
void eatline(void)
{
    while (getchar() != '\n')
        continue;
    return;
}
void init_tree(Tree* ptree) {
    ptree->root = NULL;
    ptree->size = 0;
    return;
}
bool tree_empty(const Tree* ptree) {
    return NULL == ptree->root;
}
bool tree_full(const Tree* ptree) {
    return MAXITEAMS == ptree->size;
}
int tree_count(const Tree* ptree) {
    return ptree->size;
}
bool add_item2tree(const Item_word* pi, Tree* ptree) {
    Node* new_node;
    Pair seek;

    if (tree_full(ptree)) {
        fprintf(stderr, "No memory available.\n");
        return false;
    }
    if ((seek = SeekItem(pi, ptree)).child != NULL) {
        seek.child->item_word.count++;
        return true;
    }
    new_node = MakeNode(pi);//New points to new node
    if (new_node == NULL)
    {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    ptree->size++;
    if (ptree->root == NULL)
    {
        ptree->root = new_node;
    }
    else
    {
        AddNode(new_node, ptree->root);
    }
    return true;          
}
bool in_tree(const Item_word* pi, Tree* ptree) {
    return (SeekItem(pi, ptree).child == NULL) ? false : true;
}
bool del_item(const Item_word* pi, Tree* ptree) {
    Pair look;
    look = SeekItem(pi, ptree);

    if (look.child == NULL)
    {
        return false;
    }
    if (look.child->item_word.count > 0)
    {
        look.child->item_word.count--;
    }
    else
    {
        if (look.parent == NULL)
        {
            DeleteNode(&ptree->root);
        }
        else if (look.parent->left == look.child)
        {
            DeleteNode(&look.parent->left);
        }
        else
        {
            DeleteNode(&look.parent->right);
        }
        ptree->size--;
    }
    return true;
}
bool traverse(const Tree* ptree, void(*pfun)(Item_word item)) {
    if (ptree != NULL)
    {
        InOrder(ptree->root, pfun);
    }
    return;
}
void del_all(Tree* ptree) {
    if (ptree != NULL)
    {
        DeleteAllNodes(ptree->root);
    }
    ptree->root = NULL;
    ptree->size = 0;
    return;
}
const Item_word* whereintree(const Item_word* pi, const Tree* ptree) {
    Node* pn;

    pn = SeekItem(pi, ptree).child;
    return NULL == pn ? NULL : &(pn->item_word);
}

//**************函数-main显示用
int menu(void)
{
    int ch;

    puts("==============================================");
    puts("           Word counting program");
    puts("Enter the letter corresponding to your choice:");
    puts("     s) show word list      f) find a word");
    puts("     q) quit");
    puts("==============================================");
    printf("Please you choose: ");
    while (ch = get_first(), NULL == strchr("sfq", ch))
    {
        printf("Please enter s, f or q: ");
    }
    return ch;
}



void findword(const Tree* pt)
{
    char word[SLEN];
    Item_word entry;
    const Item_word* pi;

    if (tree_empty(pt))
    {
        puts("No words in this text.");
        return;
    }
    printf("Please enter a word: ");
    s_get(word, 80);
    strcpy_s(entry.word,SLEN, word);      //把word数组中的单词复制到二叉树的项目中;
    pi = whereintree(&entry, pt); //寻找单词在二叉树中的位置;
    if (NULL == pi)
    {
        printf("Word %s doesn't exist in this text.\n", word);
    }
    else
    {
        printf("Word %s appeared %d times in this text.\n", word, pi->count);
    }
    return;
}

void print_all_items(Item_word item)
{
    printf("Word %s appeared %d times totally in this text.\n", item.word, item.count);
    return;
}
void showwords(const Tree* pt)
{
    if (tree_empty(pt)) //使用二叉树存储的单词若为空则表示无单词;
    {
        puts("No words in this text.");
    }
    else
    {
        traverse(pt, print_all_items);
    }
    return;
}
int get_first(void)
{
    int ch;

    do
    {
        ch = tolower(getchar());
    } while (isspace(ch));
    eatline();
    return ch;
}


//*************main函数！！！！！！！！！！！
void p17_7(void) {
    Tree wordcount;
    FILE* fp;
    char filename[SLEN];
    char word[SLEN];
    Item_word entry;
    char choice;

    printf("Please enter a filename: ");
    s_get(filename, SLEN);

    fopen_s(&fp, filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Can't open file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    init_tree(&wordcount); //初始化一个二叉树;
    while (1 == fscanf_s(fp, "%80s", word, 80) && !tree_full(&wordcount))
    {
        strcpy_s(entry.word,SLEN, word);
        add_item2tree(&entry, &wordcount);
    }
    while ((choice = menu()) != 'q')
    {
        switch (choice)
        {
        case 's':
        {
            showwords(&wordcount);
            break;
        }
        case 'f':
        {
            findword(&wordcount);
            break;
        }
        }
        printf("\n\n\n\n\n\n\n\n\n\n");
    }
    del_all(&wordcount);
    if (fclose(fp) != 0)
    {
        fprintf(stderr, "Can't close file %s\n", filename);
    }
    puts("Done.");

    return;

}
/*-------------p17_6-------------*/
bool in_array(int* sarray, int n, int obj) {
    bool found = false;
    int head = 0;
    int end = n - 1;
    int mid = 0;
    
    while (head < end) {
        mid = (head + end) / 2;
        if (obj < sarray[mid])
            end = mid - 1;
        else if (obj > sarray[mid])
            head = mid + 1;
        else {
            found = true;;
            break;
        }
    }
    if (sarray[head] == obj || sarray[end] == obj)
        return true;
    return found;
}
void p17_6(void) {
    int sarray[10] = { 0,1,2,3,4,5,6,7,8,9 };
    int obj = 0;
    printf("Enter a digit :(q to quit)\n");
    while (1 == scanf_s("%d", &obj)) {
        if (in_array(sarray, 10, obj))
            printf("Digit %d is in the array.\n",obj);
        else
            printf("it\'s not there.\n");
        puts("You can enter another digit:\n");
    }
}

/*-------------p17_5-------------*/

char* s_get(char* st, int n) {
    char* val;
    char* find;
    val = fgets(st, n, stdin);//成功返回第一个参数
    if (val) {
        find = strchr(st, '\n');
        if (find)
            *find = '\0';
        else
            while (getchar() != '\n')
                continue;
    }
    return val;
}
void init_stack(stack* ps) {
    ps->top = 0;
    return;
}

bool full_stack(const stack* ps) {
    return MAXSIZE == ps->top;
}
bool empty_stack(const stack* ps) {
    return 0 == ps->top;
}
bool push(item val, stack* ps) {
    if (full_stack(ps))
        return false;
    else {
        ps->data[ps->top] = val;
        ps->top++;
        return true;
    }
}

bool pop(item* val, stack* ps) {
    if (empty_stack(ps))
        return false;
    else {
        ps->top--;
        *val = ps->data[ps->top];        
        return true;
    }
}

void p17_5(void) {
    stack st;
    item ch;//接收弹出
    item temp[MAXSIZE];    

    init_stack(&st);
    printf("please enter a string (q to quit):\n");
    while (s_get(temp, MAXSIZE) != NULL && strcmp(temp,"q")!=0 ) {
        int index = 0;
        while (temp[index] != '\0')
            push(temp[index++] ,&st);
        printf("Reversing order :\n");
        while (!empty_stack(&st)) {
            pop(&ch, &st);//顺序出栈
            putchar(ch);
        }
        puts("\nYou can enter a string again(q to quit)");
    }
    puts("Quit!");
    return;
}

/*-------------p16_7-------------*/
void show_d_array(const double ar[], int n) {
    for (int i = 0; i < n; i++) 
        printf("%lf ", ar[i]);
    
    putchar('\n');
}
double* new_d_array(int n, ...) {    
    va_list ap;//声明一个存储参数的对象
    va_start(ap, n);//将ap初始化为参数列表
    double* pt;
    pt = (double*)malloc(n * sizeof(double));    
    for (int i = 0; i < n; i++)
        pt[i] = va_arg(ap, double);
    va_end(ap);
    return pt;

}
void p16_7(void) {
    double* p1;
    double* p2;
    p1 = new_d_array(5, 1.2, 2.3, 3.4, 4.5, 5.6);
    p2 = new_d_array(4, 100.0, 20.00, 8.08, -1890.0);
    show_d_array(p1, 5);
    show_d_array(p2, 4);
    free(p1);
    free(p2);
    return;
}
/*-------------p16_5-------------*/
void rand_draw(int* source, int num, int n) {
    int index = 0;
    int temp = 0;
    srand((unsigned int)time(0));
    for (int i = 0; i < n; i++) {
        index = rand() % num;
        temp = source[index];
        printf("No%3d. 30142022%d. Congratulations!\n", i + 1, temp);
        source[index] = source[num - 1];//swap
        source[num - 1] = temp;
        num -= 1;
    }
    return;
}
void p16_5(void) {
    int source[50];
    for (int i = 0; i < 30; i++)
        source[i] = i+24;
    rand_draw(source, 30, 10);
    return;
}

/*-------------p16_4-------------*/
void delay(double n) {
    clock_t begin = clock();
    clock_t end = clock();
    while (((double)end - (double)begin) / CLOCKS_PER_SEC < n) {
        end = clock();
    }
    return;
}
void p16_4(void) {
    for (int i = 0,a = 'a'; i < 26; i++,a++) {
        printf("%c ", a);
        delay(0.5);
    }
    printf("Done!\n");
}

/*-------------p16_3-------------*/
CARTISIAN p2c_convert(struct polar* polar) {
    CARTISIAN(cartisian);
    cartisian.x = polar->r * cos(DEG2RAD(polar->t));
    cartisian.y = polar->r * sin(DEG2RAD(polar->t));
    return cartisian;
}
void p16_3(void) {
    POLAR(polar) = { sqrt(128),45 };    
    CARTISIAN result = p2c_convert(&polar);
    printf("r = %.1f, theat = %.1f°\n"
        "x = %.1f, y = %.1f", polar.r, polar.t, result.x, result.y);
    return;
}

/*-------------p16_2-------------*/
void p16_2(void) {
    float x = 2, y = 2;
    printf("Digit %.1f and digit %.1f 's harmonic mean is %.1f\n", x, y, HARMEAN(x, y));
    return;
}

/*-------------p15_6-------------*/
struct message {
    //位字段
    unsigned int font : 8;
    unsigned int size : 7;
    unsigned int align : 2;
    unsigned int bold : 1;
    unsigned int italic : 1;
};
void show_message(struct message* ps) {
    printf("%5s %5s %10s %5s %5s\n", "ID", "SIZE", "ALIGNMENT", "B", "I");
    char align[10];
    switch (ps->align) {
    case 0:strcpy_s(align, 10,"left"); break;
    case 1:strcpy_s(align, 10, "middle"); break;
    case 2:strcpy_s(align, 10, "right"); break;
    }
    printf("%5d %5d %10s %5s %5s\n",
        ps->font, ps->size, align, ps->bold == 0 ? "off" : "on", ps->italic == 0 ? "off" : "on");
    return;
}
void show_choices(void) {
    printf("a)change font\tb)change size\n"
        "c)change alignment\td)toggle bold\n"
        "e)toggle italic\tq)quit\n");
    return;
}
void p15_6(void) {
    struct message text1 = {1,12,0,0,0 };//初始化
    struct message * ps = &text1;
    show_message(ps);
    putchar('\n');
    show_choices();
    char ch = 0;
    while (1 == scanf_s("%c", &ch,1) && ch != 'q') {
        while (getchar() != '\n')
            continue;
        
        switch (ch) {
        case 'a': {
            printf("Enter font(0~255):");
            int font = 0;
            if (scanf_s("%d", &font) == 1) 
                ps->font = font;
            else
                printf("modified error!\n");
            while (getchar() != '\n')
                continue;
            
            break;
        }
        case 'b': {
            printf("Enter font size(0~127):");
            int size = 0;
            
            if (scanf_s("%d", &size) == 1)
                ps->size = size;
            else
                printf("modified error!\n");
            while (getchar() != '\n')
                continue;
            break;
        }
        case 'c': {
            printf("Enter alignment(0~2):");
            int align = 0;
            
            if (scanf_s("%d", &align) == 1)
                ps->align = align;
            else
                printf("modified error!\n");
            while (getchar() != '\n')
                continue;
            break;
        }
        case 'd': {
            printf("Enter bold?(0~1):");
            int bold = 0;
            
            if (scanf_s("%d", &bold) == 1)
                ps->bold = bold;
            else
                printf("modified error!\n");
            while (getchar() != '\n')
                continue;
            break;
        }
        case 'e': {
            printf("Enter italic?(0~255):");
            int italic = 0;
            
            if (scanf_s("%d", &italic) == 1)
                ps->italic = italic;
            else
                printf("modified error!\n");
            while (getchar() != '\n')
                continue;
            break;
        }
        default:printf("wrong choice!\n"); exit(-1);
        }
        show_message(ps);
        show_choices();
    }
    return;

}

/*-------------p15_5-------------*/
unsigned int rotate(unsigned int dig, int n) {
    if (dig == 0)
        return 0;
    //确认共几位二进制
    int count = 1;
    unsigned int copy1 = dig;
    unsigned int copy2 = dig;
    while (copy1 != 1) {
        count++;
        copy1 >>= 1;
    }
    int* np;
    np = (int*)malloc(sizeof(int) * count);
    for (int i = 0; i < count; i++,copy2>>=1) {
        //取位
        np[i] = copy2 & 01;
        printf("the binary :%d\n", np[i]);
    }
    //左移
    dig <<= n;
    printf("the dig is %d: %s\n", dig,i2b(dig));

    //替换出去的高位
    for (int i = 0; i <n; i++) {
        int mask = np[count-1-i] << (n-1 - i);
        dig |= mask;
        printf("the replaced num is %d\n", np[count-1-i]);
    }
    printf("the dig is %d: %s\n", dig, i2b(dig));
    free(np);
    return dig;
}
void p15_5(void) {
    int dig = 0b100110111;
    int n = 5;
    int result;
    result = rotate(dig, n);
    printf("the digit %19d: %s\n",
        dig, i2b(dig));
    printf("after convert is %12d: %s\n",
        result, i2b(result));
    return;
}

/*-------------p15_2-------------*/
void show_bitoperate(void) {
    printf("You van choose the operations following(q to quit):\n");
    printf("a.~\tb.&\nc.|\td.^\n");
    return;
}
void bitoperate(char* ch,char* new,char choice) {
    int n = b2i(ch);
    printf("the n is %d\n", n);
    switch (choice){
    case 'a':n = ~n; break;
    case 'b':n &= 01; break;
    case 'c':n |= 01; break;
    case 'd':n ^= 01; break;
    default:printf("Entered wrong choice!\n"); exit(-1);
    }
    for (int i = 31 - 1; i >= 0; i--, n >>= 1) {
        new[i] = (01 & n) + '0';
    }
    new[31] = '\0';
    return;
}
void p15_2(void) {
    printf("Enter a string of Binary string:(q to quit)");
    char b_stirng[32];
    char b_new[32];
    while ((scanf_s("%s", b_stirng,32) == 1)&& (b_stirng[0]!='q')) {
        while (getchar() != '\n')
            continue;
        show_bitoperate();
        char c;
        c = getchar();
        while (getchar() != '\n')
            continue;
        printf("your input is %c\n", c);
        bitoperate(b_stirng, b_new, c);
        printf("the opeartion %c is %s\n\n", c, b_new);
        printf("you can enter again:(q to quit):");

    }
    return;
}

/*-------------p15_1-------------*/
char* i2b(int n) {
    static char ch_b[32+1];
    for (int i = 32 - 1; i >= 0; i--,n>>=1) 
        ch_b[i] = (01 & n) + '0';
    ch_b[32] = '\0';
    //printf("the ch is %s\n", ch_b);
    return ch_b;
}
int b2i(char* ch) {
    int n = 0;
    if (ch[0] == '0') {
        for (int i = strlen(ch) - 1, j = 0; i >= 0; i--, j++) {
            n += (ch[i] - '0') * pow(2 , j);
        }
        return n;
    }
    else if (ch[0] == '1') {
        int index = 1;
        
        for (int i = strlen(ch) - 1, j = 0; i > 0; i--, j++) {
            int middle = ch[i] == '0' ? 1 : 0;
            n += middle * pow(2, j);
        }
        n += 1;
        return (-1*n);
    }
    else
        exit(EXIT_FAILURE);
}
void p15_1(void) {
    char* pbin = "11001001";
    int bin = 73;
    printf("int to binary: %d turns to be %s\n", bin, i2b(bin));
    printf("binary to int: %s turns to be %d\n", pbin, b2i(pbin));
    return;
}

/*-------------p14_11-------------*/
void show_menu(void) {
    printf("which of the following processes you want to exert on the data?"
        "(q to quit)\n");
    printf("a.sin\tb.square root\nc.exp\td.log\n");
    return;
}
void transform(double* source, double* target, int n, double(*fp)(double)) {
    for (int i = 0; i < n; i++) {
        target[i] = fp(source[i]);
    }
    printf("source array is:\n");
    for (int i = 0; i < 100; i++) {
        printf("%.1f ", source[i]);
        if ((i+1) % 10 == 0)
            putchar('\n');
    }
    printf("\n\ntarget array is:\n");
    for (int i = 0; i < 100; i++) {
        printf("%.1f ", target[i]);
        if ((i+1) % 10 == 0)
            putchar('\n');
    }
    return;
}
void p14_11(void) {
    double(*fp)(double) = NULL;
    show_menu();
    char ch;
    double source[100];
    double target[100];
    for (int i = 0; i < 100; i++)
        source[i] = i;
    while (scanf_s("%c", &ch) == 1 && ch != 'q') {
        while (getchar() != '\n')
            continue;
        if (ch >= 'a' && ch <= 'd') {
            switch (ch) {
            case 'a':fp = sin; break;
            case 'b':fp = sqrt; break;
            case 'c':fp = exp; break;
            case 'd':fp = log; break;
            }
        }
        else {
            printf("Enter the right option!\n");
            show_menu();
            continue;
        }        
        transform(source, target, 100, fp);
        show_menu();
    }
    
    
    return;
}

/*-------------p14_5-------------*/
struct name {
    char fname[20];
    char lname[20];
};
struct student {
    struct name s_name;
    float grade[3];
    float average;
};

void set_students(struct student list[], int n) {
    for (int i = 0; i < n; i++) {        
        for (int j = 0; j < 3; j++) {
            printf("Please enter the score of subject %d for %s %s:\n", j + 1, list[i].s_name.fname, list[i].s_name.lname);
            while (scanf_s("%g", &list[i].grade[j])!=1) {
                while (getchar() != '\n')
                    continue;
                printf("Enter the right grade.\n");
            }
        }        
    }
    return;
}
void get_averages(struct student list[], int n) {
    double aggregate = 0.0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            aggregate += list[i].grade[j];
        }
        list[i].average = aggregate / 3;
        aggregate = 0.0;        
    }
    return;
}
void show_messages(const struct student list[], int n) {
    printf("%+20s %10s %10s %10s %15s\n", "name", "grade 1", "grade 2", "grade 3", "average grade");
    for (int i = 0; i < n; i++) {
        printf("%10s%10s %10.1f %10.1f %10.1f %15.1f\n",
            list[i].s_name.fname, list[i].s_name.lname, 
            list[i].grade[0], list[i].grade[1], list[i].grade[2], 
            list[i].average);
    }
    return;
}
void show_averages(const struct student list[], int n) {
    double aggregate= 0.0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            aggregate += list[i].grade[j];
        }
    }
    aggregate /= (3 * n);
    printf("The average grade of the class is %lf\n", aggregate);
}
void p14_5(void) {
#define CSIZE 4
    struct student classes[CSIZE] =
    {
        {"Harry", "Potter"},
        {"Hermoine", "Granger"},
        {"Ronald", "Weasley"},
        {"Wundt", "Asim"}
    };
    set_students(classes, CSIZE);
    get_averages(classes, CSIZE);
    show_messages(classes, CSIZE);
    show_averages(classes, CSIZE);
    #undef CSIZE
    return;
}

/*-------------p14_4-------------*/
#define N  20
struct names {
    char fname[N];
    char mname[N];
    char lname[N];
};
struct id {
    char number[N];
    struct names name;
};
void show_id(const struct id identi[], int n)
{
    printf("All the ID messages:\n");
    for (int i = 0; i < n; i++) {
        if (identi[i].name.mname[0] == '\0') {
            printf("%s,%s. -- %s\n", identi[i].name.fname, identi[i].name.lname, identi[i].number);
        }
        else {
            printf("%s,%c.%s. -- %s\n", identi[i].name.fname, identi[i].name.mname[0], identi[i].name.lname, identi[i].number);
        }
    }
    return;
}
void p14_4(void)
{    
    struct id iden[4] = {
        {"12345","Harry","James","Potter"},
        {"23456","Hermione","Jean","Granger"},
        {"34567","Ronald Bilius","Ron","Weasley"},
        {"112303","Wundt","","Asim"}
    };
    show_id(&iden, 4);
    #undef N
    return;
}

/*-------------p14_2-------------*/
struct month {
    char name[10];
    char mon[4];
    int days;
};
struct month months[12] = {
        {"January","jan",31},
        {"Fenruary","feb",29},
        {"March","mar",31},
        {"April","apr",30},
        {"May","may",31},
        {"June","jun",30},
        {"July","jul",31},
        {"August","aug",31},
        {"September","sep",30},
        {"October","oct",31},
        {"November","nov",30},
        {"December","dec",31}
};
int day_count(int day, char* month)
{
    int count = 0;
    int index = 0;
    while (month[index] != '\0') {
        month[index] = tolower(month[index]);  
        index++;
    }
    month[3] = '\0';
    index = 0;

    for (int i = 0; i < 12; i++) {
        if (strcmp(month, months[i].mon) == 0)
            index = i+1;
    }
    for (int j = 0; j < index; j++) {
        count += months[j].days;
    }
    count += day;
    return count;
}
void p14_2(void)
{
    extern struct month months[];
    printf("Please enter day, month and year (q to quit): ");
    int day; 
    char month[11]; 
    int year;
    while (scanf_s("%d %11s %d", &day, month,11, &year) == 3) {
        if (year % 4 == 0)
            months[1].days = 29;
        else
            months[1].days = 28;

        int count = day_count(day, month);
        if (count)
            printf("There are %d days from the beginning of %d to %s %d\n""you can enter again:(q to quit)", count, year, month, day);
        else
            printf("ERROR:enterd wrong datas!\n"
                "you can enter again:(q to quit)");
    }
    printf("DONE!\n");
    return;
}


/*-------------p14_1-------------*/

int days(char* month)
{
    int count = 0;
    int index = 0;
    for (int i = 0; i < 3; i++) {
        month[i] = tolower(month[i]);
    }
    for (int i = 0; i < 12; i++) {
        if(strcmp(month, months[i].mon) == 0)
            index = i+1;                   
    }
    for (int j = 0; j < index; j++){
        count += months[j].days;
    }
    return count;    
}
void p14_1(void)
{   
    extern struct month months[];
    printf("Enter the short for the month:(q to quit)");
    char month[5];
    
    while (scanf_s("%3s", month, 4) == 1 && month[0] != 'q') {
       int count;
       count = days(month);
       if (count) {
        printf("The congragate number of days is %d\n", count);
        printf("Done\n");
        printf("you can enter again:(q to quit)");
    }
    else
        printf("ERRPR:Input must be right.\nyou can enter again:");
    }   
    
    
        
    
    return;
    



}

/*-------------p13_12-------------*/
void eliminate_noise(char* filename,const int x,const int y)
{
    //打开文件
    FILE* fp;
    fopen_s(&fp, filename, "r+");
    if (fp == NULL)
    {
        printf("Can't open file %s.\n", filename);
        exit(EXIT_FAILURE);
    }
    printf("file %s opened.\n", filename);

    if (x <= 0 || y <= 0) {
        printf("行数或列数不合法！\n");
        exit(-1);
    }
    //消除噪声
    int** image = NULL;
    image = (int**)malloc(x * sizeof(int*));
    if (image == NULL)
        exit(EXIT_FAILURE);
    for (int i = 0; i < x; i++)
    {
        image[i] = (int*)malloc(y * sizeof(int));
        if (image[i] == NULL)
            exit(EXIT_FAILURE);
    }

    //写入数组
    
    for (int i = 0; i < x; i++)
    {
        int j = 0;
        int ch;
        while ((ch = getc(fp))!=EOF && ch!='\n')
        { 
            if (isdigit(ch))
            {
                image[i][j] = ch - '0';
                j++;
            }
            else
                continue;
          
        }
        for (int k = 0; k < y; k++)
            printf("%d ", image[i][k]); 
        putchar('\n');
    }
    //处理数组（消噪）
    for (int i = 0; i < x; i++){    
        for (int j = 0; j < y; j++) {
            //首行
            if (i == 0) {
                //左上顶点
                if (j == 0) {
                    if ((image[i][j] - image[i][j + 1]) > 1 && (image[i][j] - image[i + 1][j]) > 1)
                        image[i][j] = (image[i + 1][j] + image[i][j + 1]) / 2;
                }                    
                //右上顶点
                else if (j == y - 1) {
                    if ((image[i][j] - image[i][j - 1]) > 1 && (image[i][j] - image[i + 1][j]) > 1)
                        image[i][j] = (image[i + 1][j] + image[i][j - 1]) / 2;
                }                    
                //首行内点
                else {
                    if ((image[i][j] - image[i][j + 1]) > 1 && (image[i][j] - image[i + 1][j]) > 1 && (image[i][j] - image[i][j-1]) > 1)
                        image[i][j] = (image[i + 1][j] + image[i][j + 1] + image[i][j - 1]) / 3;
                }       
            }
            //尾行
            else if (i == x-1) {
                //左下顶点
                if (j == 0) {
                    if ((image[i][j] - image[i][j + 1]) > 1 && (image[i][j] - image[i - 1][j]) > 1)
                        image[i][j] = (image[i - 1][j] + image[i][j + 1]) / 2;
                }
                //右下顶点
                else if (j == y - 1) {
                    if ((image[i][j] - image[i][j - 1]) > 1 && (image[i][j] - image[i - 1][j]) > 1)
                        image[i][j] = (image[i - 1][j] + image[i][j - 1]) / 2;
                }
                //尾行内点
                else {
                    if ((image[i][j] - image[i][j - 1]) > 1 && (image[i][j] - image[i][j+1]) > 1 && (image[i][j] - image[i - 1][j]) > 1)
                        image[i][j] = (image[i][j-1] + image[i][j + 1] + image[i-1][j]) / 3;
                }
            }
            //首列内点
            if (j == 0) {  
                if (i == 0 || i == x - 1)
                    break;
                if ((image[i][j] - image[i+1][j]) > 1 && (image[i][j] - image[i][j + 1]) > 1 && (image[i][j] - image[i - 1][j]) > 1)
                   image[i][j] = (image[i+1][j] + image[i][j + 1] + image[i - 1][j]) / 3;                
            }
            //尾列内点
            else if (j == y-1) {
                if (i == 0 || i == x - 1)
                    break;
                if ((image[i][j] - image[i + 1][j]) > 1 && (image[i][j] - image[i][j - 1]) > 1 && (image[i][j] - image[i - 1][j]) > 1)
                    image[i][j] = (image[i + 1][j] + image[i][j - 1] + image[i - 1][j]) / 3;
            }

            //数组内部值：
            if ((image[i][j] - image[i + 1][j]) > 1 && (image[i][j] - image[i][j - 1]) > 1 && (image[i][j] - image[i - 1][j]) > 1 && (image[i][j] - image[i][j+1]) > 1) {
                image[i][j] = (image[i - 1][j] + image[i + 1][j] + image[i][j - 1] + image[i][j + 1]) / 4;
                printf("haha\n");
            }


        }

    }

    //写入文件
    rewind(fp);
    for (int j = 0; j < x; j++)
    {
        for (int i = 0; i < y; i++)
        {
            fprintf(fp, "%d", image[j][i]);
            if (i < y - 1)
                putc('-', fp);
            else
                putc('\n', fp);
        }
    }    

    //清理内存
    for (int i = 0; i < x; i++)
        free(image[i]);
    free(image);  

    fclose(fp);
    fp = NULL;
    return;
}

void p13_13(void)
{
    printf("Enter the number of x and y pixels:");
    int x_pixel, y_pixel;
    scanf_s("%5d%5d", &x_pixel, &y_pixel);
    //创建0-9代表的灰度图
    const char* imagedig = "imagedig.txt";
    FILE* fp_imagedig;
    fp_imagedig = openfile(imagedig);

    //将灰度数值写入文件
    srand((unsigned int)500);
    for (int j = 0; j < x_pixel; j++)
    {
        for (int i = 0; i < y_pixel; i++)
        {
            int roll;
            roll = rand() % 10;

            fprintf(fp_imagedig, "%d", roll);
            if (i < y_pixel-1)
                putc(' ', fp_imagedig);
            else
                putc('\n', fp_imagedig);
        }
    }
    fclose(fp_imagedig);
    fp_imagedig = NULL;

    //处理噪声
    eliminate_noise(imagedig, x_pixel, y_pixel);

    //读取灰度值文件
    fopen_s(&fp_imagedig, imagedig, "r+");
    if (fp_imagedig == NULL)
        exit(EXIT_FAILURE);
    int ch;
    int** dig = NULL;
    dig = (int**)malloc(x_pixel * sizeof(int*));
    if (dig == NULL)
        exit(EXIT_FAILURE);
    for (int i = 0; i < x_pixel; i++)
    {
        dig[i] = (int*)malloc(y_pixel * sizeof(int));
        if (dig[i] == NULL)
            exit(EXIT_FAILURE);
    }        
    
    int count = 0;//用于计数dig数组到末尾
    while ((ch = getc(fp_imagedig)) != EOF)
    {
        if ((isdigit(ch)))
        {
            dig[count / x_pixel][count % x_pixel] = ch - '0';
            /*多次调用malloc分配的地址不一定连续，因实际物理内存可能分页，所以间隔分配。
            * 因此不用下行代码↓
            //*(*dig + count) = ch - '0';
            printf("dig[%d] = %d, address:%p\n", 
                count, dig[count/x_pixel][count%x_pixel],&dig[count / x_pixel][count % x_pixel]);
            */
            count++;
            if (count > x_pixel * y_pixel - 1)
                break;//防止溢出数组！                       
        }
        else
            continue;
    }
    count = 0;
    printf("so the content is:\n");
    for (int i = 0; i < x_pixel; i++)
    {
        for (int j = 0; j < y_pixel; j++)
        {
            printf("%d ", dig[i][j]);
        }putchar('\n');
    }puts("\n\n");
    if(fclose(fp_imagedig))
        exit(EXIT_FAILURE);
    fp_imagedig = NULL;

    /// 画出对应图象
    printf("so the image is:\n");
    for (int i = 0; i < x_pixel; i++)
    {
        for (int j = 0; j < y_pixel; j++)
        {
            int temp = 0;
            switch (dig[i][j])
            {
            case 0:
            {
                temp = '\'';
                break;
            }
            case 1:
            {
                temp = '.';
                break;
            }
            case 2:
            {
                temp = ',';
                break;
            }
            case 3:
            {
                temp = '\"';
                break;
            }
            case 4:
            {
                temp = ':';
                break;
            }
            case 5:
            {
                temp = '-';
                break;
            }
            case 6:
            {
                temp = '+';
                break;
            }
            case 7:
            {
                temp = '*';
                break;
            }
            case 8:
            {
                temp = '%';
                break;
            }
            case 9:
            {
                temp = '#';
                break;
            }
            }
            printf("%c ",temp);
        }putchar('\n');
    }
    printf("Done!\n");

    
    for (int i = 0; i < x_pixel; i++)
        free(dig[i]);
    free(dig);
    return;

}

/*-------------p13_12-------------*/
FILE* openfile(char* filename)
{
    FILE* fp;
    fopen_s(&fp, filename, "w+");
    if (fp == NULL)
    {
        printf("Can't open file %s.\n", filename);
        exit(EXIT_FAILURE);
    }
    printf("file %s opened.\n", filename);
    return fp;
}
void p13_12(void)
{
    //创建0-9代表的灰度图
    char* imagedig = "imagedig.txt";
    FILE* fp_imagedig;
    fp_imagedig = openfile(imagedig);
    
    //将灰度数值写入文件
    srand((unsigned int)time(0));
    for (int j = 0; j < 20; j++)
    {
        for (int i = 0; i < 30; i++)
        {
            int roll;
            roll = rand() % 10 ;
            
            fprintf(fp_imagedig, "%d", roll);
            if (i < 29)
                putc(' ', fp_imagedig);
            else
                putc('\n', fp_imagedig);
        }
    }
    fclose(fp_imagedig);
    fp_imagedig = NULL;

    //读取灰度值文件
    fopen_s(&fp_imagedig, imagedig, "r+");
    if (fp_imagedig == NULL)
        exit(EXIT_FAILURE);    
    int ch;
    int dig[20][30];
    int(* temp)[30];
    temp = dig;//用于接收每个数字
    int count = 0;//用于计数dig数组到末尾
    while ((ch = getc(fp_imagedig)) != EOF)
    {        
        if ((isdigit(ch)))
        {
            *(*temp + count)= ch - '0';
            count++;
            if (count > 20 * 30-1)
                break;//防止溢出数组！                       
        }
        else
            continue;  
        
              
    }
    printf("so the content is:\n");
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            
            printf("%d ", dig[i][j]);
        }putchar('\n');
    }puts("\n\n");
    fclose(fp_imagedig);
    fp_imagedig = NULL;   

    /// 画出对应图象
    printf("so the image is:\n");
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            int temp;
            switch (dig[i][j])
            {
            case 0:
            {
                temp = '\'';
                break;
            }
            case 1:
            {
                temp = '.';
                break;
            }
            case 2:
            {
                temp = ',';
                break;
            }
            case 3:
            {
                temp = '\"';
                break;
            }
            case 4:
            {
                temp = ':';
                break;
            }
            case 5:
            {
                temp = '-';
                break;
            }
            case 6:
            {
                temp = '+';
                break;
            }
            case 7:
            {
                temp = '*';
                break;
            }
            case 8:
            {
                temp = '%';
                break;
            }
            case 9:
            {
                temp = '#';
                break;
            }
            }
            printf("%c ", temp);
            
        }putchar('\n');
    }
    printf("Done!\n");


    return;
    
}

/*-------------p13_10-------------*/
void p13_10(void)
{
    printf("Enter the finame of waht you want to demonstrate:");
    char file[30];
    scanf_s("%s", file, 30);
    FILE* fp;
    fopen_s(&fp, file, "r");
    if (fp==NULL)
    {
        printf("Can't open file %s", file);
        exit(EXIT_FAILURE);
    }
    printf("the file %s has been opened.\n", file);

    printf("Enter the location which you want to type:(nagative or q to quit)");
    long n;
    while ((1 == scanf_s("%ld", &n)) && n >= 0)
    {
        
        fseek(fp, 0L, SEEK_SET);
        if (0 == fseek(fp, n, SEEK_SET))
        {
            int ch;
            while (((ch = getc(fp)) != EOF) && ch != '\n')
            {
                putc(ch, stdout);
            }
            putchar('\n');
        }
        else
            exit(EXIT_FAILURE);
        
        printf("Enter the location which you want to type:(nagative or q to quit)");
    }
    fclose(fp); fp = NULL;
    printf("file has been closed.\n");
    return;
    
}

/*-------------p13_7-------------*/
void p13_7(void)
{
    //打开文件1
    printf("Enter the filename of the first one:");
    char file_1[30];
    scanf_s("%s", file_1,30);
    FILE* fp1;
    fopen_s(&fp1, file_1, "r");
    if (fp1 == NULL)
    {
        printf("Can't open file \"%s\"", file_1);
        exit(EXIT_FAILURE);
    }
    printf("file \"%s\" opened.\n", file_1);
    //打开文件2
    printf("Enter the filename of the second one:");
    char file_2[30];
    scanf_s("%s", file_2,30);
    FILE* fp2;
    fopen_s(&fp2, file_2, "r");
    if (fp2 == NULL)
    {
        printf("Can't open file \"%s\"", file_2);
        exit(EXIT_FAILURE);
    }
    printf("file \"%s\" opened.\n", file_2);

    int ch1 = 0, ch2 = 0;
    ch1 = getc(fp1);
    ch2 = getc(fp2);
    while (1)
    {
        while (ch1 != EOF)
        {            
            putc(ch1, stdout);  
            ch1 = getc(fp1);
            if (ch1 == '\n')
            {
                ch1 = getc(fp1);//若检测到换行，则跳过换行，并跳出循环
                break;
            }          
         
        }
        printf("\t");
        while (ch2 != EOF)
        {
            putc(ch2, stdout);
            ch2 = getc(fp2);
            if (ch2 == '\n')
            {
                ch2 = getc(fp2);//若检测到换行，则跳过换行，并跳出循环
                break;
            }

        }
        putchar('\n');

        if (feof(fp1) && feof(fp2))
        {
            break;
        }
       
    }
    fclose(fp1);
    fp1 = NULL;
    fclose(fp2);
    fp2 = NULL;
    return;
}

/*-------------p13_3-------------*/
int readfile(char* filename)
{
    FILE* fp;
    fopen_s(&fp, filename, "r+");
    if (fp == NULL)
    {
        fprintf(stderr, "Can't open file--%s !\n",filename);
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "file--%s opened!\n", filename);
    int ch,cnt = 0; 
    printf("file content:\n");
    while ((ch = getc(fp)) != EOF)
    {
        putc(ch, stdout);
        cnt++;
    }
    puts("\nDone!");
    printf("there are %d characters.\n", cnt);
    if (fclose(fp))
    {
        fprintf("Can't close file--%s", filename);
        exit(EXIT_FAILURE);
    }
    else
        fp = NULL;
        return 1;
}
void p13_3(void)
{
    printf("Enter the name of file you want to dispose:");
    char filename[30];
    fscanf_s(stdin, "%s", filename,30);
    readfile(filename);
    puts("\n\n");

    FILE* fp;
    fopen_s(&fp, filename, "r+");
    if (fp == NULL)
    {
        fprintf(stderr, "Can't open file--%s !\n", filename);
        exit(EXIT_FAILURE);
    }
    int ch;
    while (1)
    {
        ch = getc(fp);
        if (ch == EOF)
           break;
        else if(isalpha(ch))
        {
            fseek(fp, -1L, SEEK_CUR);
            putc(toupper(ch), fp);
            fseek(fp, 0L, SEEK_CUR);
        }
        else
        {
            fseek(fp, -1L, SEEK_CUR);
            putc(ch, fp);
            fseek(fp, 0L, SEEK_CUR);            
        }    
        
    }
    rewind(fp);
    fclose(fp);

    readfile(filename);
    return;
}

/*-------------p13_2-------------*/
int file_copy(FILE* source, FILE* destination)
{
    setvbuf(destination, NULL, _IOFBF, 256);
    char temp[256];
    size_t bytes;
    while ((bytes = fread(temp, sizeof(char), 256, source)) > 0)
    {
       
        fwrite(temp, sizeof(char), bytes, destination);
        printf("copying!\n");
    }
    printf("the bytes is %d\n", (int)bytes);
    if (fclose(source) || fclose(destination))
        return 0;
    else
    {
        source = NULL;
        destination = NULL;
        return 1;
    }
        
}
void p13_2(int argcount,char** argument)
{
    if (argcount < 3)
    {
        printf("Usage: %s source_file destination_file\n", argument[0]);
        exit(EXIT_FAILURE);
    }
    FILE* source_fp;
    fopen_s(&source_fp, argument[1], "rb");
    if (source_fp == NULL)
    {
        fprintf(stderr, "Can't open source file!\n");
        exit(EXIT_FAILURE);
    }
    printf("...source file has been opened.\n");

    FILE* destination_fp;
    fopen_s(&destination_fp, argument[2], "wb");
    if (!destination_fp)
    {
        fprintf(stderr, "Can't open destination file!\n");
        exit(EXIT_FAILURE);
    }
    printf("...destination file has been opened.\n");

    if (file_copy(source_fp, destination_fp) == 1)
        printf("file has been copyed!\n");
    else
        printf("Error while coping!\n");
    return;

}

/*-------------p13_1-------------*/
void p13_1(void)
{
    printf("Enter the file name you want to check: ");
    char file_name[30];
    while (fscanf_s(stdin,"%s", file_name,30) != 1)
    {
        fprintf(stderr,"Usage : filename\n");
        exit(EXIT_FAILURE);
    }
    strcat_s(file_name,sizeof file_name,"\0");
    printf("So, the file name is %s, hah!\n", file_name);
    FILE* fp;
    fopen_s(&fp, file_name, "r+");
    if (fp == NULL)
    {
        fprintf(stderr, "Can't open file %s\n",file_name);
        exit(EXIT_FAILURE);
    }
    printf("the file %s has already opened. \n", file_name);

    int ch;
    while ((ch = getc(fp)) != EOF)
        putc(ch, stdout);
    putchar('\n');
    for(int i = 0; i < (int)strlen(file_name); i++)
    {
        printf("the %dst character is %c\n",i,file_name[i]);
        putc(file_name[i], fp);
    }



    if (fclose(fp))
        printf("Error in closing file %s", file_name);
    else
        printf("Thank God! The file has been closed.\n");

    fp = NULL;

    return;
}

/*-------------p12_9-------------*/

void p12_9(void)
{
    printf("How many wordsdo you wisn to enter? \n");
    int n;
    scanf_s("%d", &n);
    printf("Enter your %d words now:\n", n);

    char** words;
    int len;
    char temp[100] = {0};
    if (words = (char**)malloc(n * sizeof(char*)))
    {
        for (int i = 0; i < n; i++)
        {
          scanf_s("%s", temp,99);
          len = strlen(temp) + 1;
          words[i] = (char*)malloc(len * sizeof(char));
          if (NULL == words[i])
          {
              printf("Memory allocation failed!\n");
              exit(-1);
          }
          strcpy_s(words[i],len, temp);
          //数组不要过界：中间为缓冲区大小。
          puts(words[i]);
          //↑从临时数组中把单词拷贝到动态分配的存储空间中;
        }

        printf("Here are your %d words:\n", n);
        for (int i = 0; i < n; i++)
        {
            puts(words[i]);
            free(words[i]);
          //  words[i] = NULL;
        }
        free(words);
     //   words = NULL;
        //↑指针仍然指向malloc分配的存储空间;
        //↑因此令指针指向NULL后防止内存滥用;

    }
    else
    {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

        
}

/*-------------p12_8-------------*/
int* make_array(int elem, int val)
{ 
    int* p = NULL;
    p = (int*)malloc(elem * sizeof(int));
    if (p == NULL)
    {
        puts("Memory allocation failed,Goodbye.");
        exit(EXIT_FAILURE);
    }
   
    for (int i = 0; i < elem; i++)
    {
        p[i] = val;
    }       
    return p;
}
void p12_8(void)
{
    int* pa;
    int size;
    int value;
    printf("Enter the number of elements: ");
    while (scanf_s("%d", &size)== 1 && size>0)
    {
        printf("Enter the initialization value: ");
        scanf_s("%d", &value);
        pa = make_array(size, value);
        if (pa)
        {
            show_array(pa, size);
            free(pa);

        }
        printf("Enter the number of elements (< 1 to quit): ");
    }
    printf("Done!\n");
}

/*-------------p12_6-------------*/
void occur_times(int *arr,int n, int j)
{
    int count = 0;
    int* p;
    p = arr;
    for (int i = 0; i < n; i++)
    {
        if (j == *p++)
            count++;
    }
    printf("Number %d occurs %d times\n", j, count);
    return;
}
void p12_6(void)
{
#define LEN 1000
    unsigned int seed = 11;
    for (int time = 0; time < 10; time++)
    {
        seed += time;
        srand((unsigned int)seed);
        int arr[LEN];
        for (int i = 0; i < LEN; i++)
        {
            arr[i] = rand() % 10 + 1;
        }
        for (int j = 1, count = 0; j < 11; j++)
        {
            occur_times(arr, LEN, j);
        }
        putchar('\n');
    }
    printf("Test completed!\n");
  
}

/*-------------p12_5-------------*/

void show_array(const int *arr, int n)
{
   
        for (int i = 0; i < n; i++)
        {

            printf("%-4d", arr[i]);
            if (!((i+1)% 8) )
                putchar('\n');
        }
        putchar('\n');
    
   
}
void sort(int *arr, int n)
{
    int temp;
    for (int i = 0; i < n-1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] > arr[i])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}
void p12_5(void)
{
#define LEN 100
    int arr[LEN];
    srand((unsigned int)time(0));
    for (int i = 0; i < LEN; i++)
    {
        arr[i] = rand() % 10 + 1;
    }
    printf("Array is:\n");
    show_array(arr, LEN);
    sort(arr, LEN);
    printf("After sorting is:\n");
    show_array(arr, LEN);

}

/*-------------p12_4-------------*/
int counter(void)
{
    static int count;
    return ++count;
}
void p12_4(void)
{
    for (int i = 0; i < 8; i++)
    {
        counter();
    }
    printf("the function counter has been called %d times.\n", counter()-1);
    return;
}

/*----------------------------------p12_2-------------------------*/
static int mode;
static double distance;
static double fuel;
void set_mode(int n)
{
    if (n > 1)
    {
        printf("Invalid mode specified. Mode %s used.\n",
            (0 == mode) ? "0(metric)" : "1(US)");
    }
    else
    {
        mode = n;
    }
    return;

}
void get_info()
{
	printf("Enter distance traveled in %s:\n",
        (0 == mode) ? "kilmoters" : "miles" );
    scanf_s("%lf", &distance);

    printf("Enter fuel comsumed in %s:\n",
        (0 == mode) ? "liters" : "gallons");
    scanf_s("%lf", &fuel);

}
void show_info()
{
    printf("Fuel consumption is %g %s:\n",
        (0 == mode) ? fuel/100/distance : distance/fuel,
        (0 == mode) ? "liters/100km" : "miles/gallons");
}