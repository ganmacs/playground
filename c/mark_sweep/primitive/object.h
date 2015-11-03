#define OBJ_SIZE sizeof(Object)
#define O_Int_SIZE sizeof(O_Int)
#define O_Pair_SIZE sizeof(O_Pair)
#define OBJ_INT_SIZE (O_Int_SIZE + OBJ_SIZE)
#define OBJ_PAI_SIZE (O_Pair_SIZE + OBJ_SIZE)

/* data type */
typedef enum {
  OBJ_INT,
  OBJ_PAIR
} ObjectType;

typedef struct {
  /* header info */
  ObjectType type;

  /* actual data */
  void* body;
} Object;

typedef struct {
  int value;
} O_Int;

typedef struct {
  Object* head;
  Object* tail;
} O_Pair;
