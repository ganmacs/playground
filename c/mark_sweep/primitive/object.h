#define OBJ_SIZE sizeof(object)
#define O_Int_SIZE sizeof(o_int)
#define O_Pair_SIZE sizeof(o_pair)
#define OBJ_INT_SIZE (O_Int_SIZE + OBJ_SIZE)
#define OBJ_PAIR_SIZE (O_Pair_SIZE + OBJ_SIZE)

/* data type */
typedef enum {
  OBJ_INT,
  OBJ_PAIR
} object_type;

typedef struct {
  /* header info */
  object_type type;
  int marked;

  /* actual data */
  void* body;
} object;

typedef struct {
  int value;
} o_int;

typedef struct {
  object* head;
  object* tail;
} o_pair;
