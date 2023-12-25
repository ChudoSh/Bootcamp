/*
Dev: BarSh
Rev: MariaP
Date: 8.8.23
Status: Test impl.
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
/*===========================Utils and declerations===========================*/
enum BOOL
{
    FALSE, 
    TRUE
};

enum FUNCS
{
    TOSTRING,
    SAY_HELLO,
    GET_NUM_MASTERS,
    FINALIZE
};

typedef void * (*vtable_t)(void *);
typedef struct Class class_t;
typedef struct Object object_t;
typedef struct Animal animal_t;
typedef struct Dog dog_t;
typedef struct Cat cat_t;
typedef struct LegendaryAnimal legendary_animal_t;

/*Object funcs*/
object_t *ObjectCtor();
void *Obj_ToString(void *this);
void *Obj_Finalize(void *this);

/*Animal funcs*/
animal_t *AnimalCtor(void *args);
void Animal_NoArgsInit(animal_t *animal_to_init);
void Animal_ArgsInit(animal_t *animal_to_init, int num_masters);
void Animal_StaticBlockOne();
void Animal_StaticBlockTwo();
void Animal_InstanceBlock();
void *Animal_ToString(void *this);
void *Animal_SayHello(void *this);
void *Animal_GetNumMasters(void *this);
void *Animal_ShowCounter(void *this);
void *Animal_Finalize(void *this);

/*Dog funcs*/
dog_t *DogCtor(void);
void Dog_Init(dog_t *dog_to_init);
void Dog_StaticBlock();
void Dog_InstanceBlock();
void *Dog_ToString(void *this);
void *Dog_SayHello(void *this);
void *Dog_Finalize(void *this);

/*Cat funcs*/
cat_t *CatCtor(void *args);
void Cat_StaticBlock();
void Cat_InitNoArgs(cat_t *cat_to_init);
void Cat_InitArgs(cat_t *cat_to_init, void *args);
void *Cat_ToString(void *this);
void *Cat_Finalize(void *this);

/*LegendaryAnimal funcs*/
legendary_animal_t *LegendaryCtor();
void Legendary_StaticBlock();
void *LegendaryAnimal_ToString(void *this);
void *LegendaryAnimal_SayHello(void *this);
void *LegendaryAnimal_Finalize(void *this);


/*Static funcs*/
static void foo(animal_t *animal);

/*================================Classes=====================================*/
struct Class
{
    char *name; 
    class_t *parent;
    size_t size;
    vtable_t *vtable;   
};

struct Object
{
    class_t *metadata;
};

static int counter;
struct Animal 
{
    object_t parent;
    int num_legs;
    int num_masters;
    int ID;
}; 

struct Dog 
{
    animal_t parent;
    int num_legs;
}; 

struct Cat 
{
    animal_t parent;
    char *colors;
    int num_masters;
}; 

struct LegendaryAnimal 
{
    cat_t parent;
}; 

static vtable_t obj_func[] = {Obj_ToString, NULL, NULL, NULL ,Obj_Finalize};
static vtable_t animal_func[] = {Animal_ToString, 
                                 Animal_SayHello, 
                                 Animal_GetNumMasters,
                                 Animal_Finalize};
static vtable_t dog_func[] = {Dog_ToString, 
                              Dog_SayHello, 
                              Animal_GetNumMasters,
                              Dog_Finalize};
static vtable_t cat_func[] = {Cat_ToString, 
                              Animal_SayHello, 
                              Animal_ShowCounter,
                              Animal_GetNumMasters,
                              Cat_Finalize};
static vtable_t legendary_func[] = {LegendaryAnimal_ToString,
                                    LegendaryAnimal_SayHello,  
                                    Animal_GetNumMasters, 
                                    LegendaryAnimal_Finalize}; 


/*==============================Metadata init=================================*/
static const class_t ObjClass = {"Object", NULL, sizeof(object_t),obj_func};
static const class_t AnimalClass = {"Animal", (class_t *)&ObjClass,
                                     sizeof(animal_t), animal_func};
static const class_t DogClass = {"Dog", (class_t *)&AnimalClass,sizeof(dog_t), dog_func};
static const class_t CatClass = {"Cat",(class_t *)&AnimalClass, sizeof(cat_t), cat_func};

static const class_t LegendaryClass = {"LegendaryAnimal", (class_t *)&CatClass, 
                                        sizeof(legendary_animal_t), 
                                        legendary_func}; 
/**********************************Main****************************************/
#define FILE_NAME ("j2c_output.text")

int main()
{
    animal_t *Array[5] = {NULL};
    object_t *obj = ObjectCtor();
    animal_t *animal = AnimalCtor(NULL);
    dog_t *dog = DogCtor();
    cat_t *cat = CatCtor(NULL);
    legendary_animal_t *legend = LegendaryCtor(NULL);
    int i = 0; 
    
    Animal_ShowCounter(animal);

    printf("%d\n", animal->ID);
    printf("%d\n", ((animal_t *)dog)->ID);
    printf("%d\n", ((animal_t *)cat)->ID);
    printf("%d\n", ((animal_t *)legend)->ID);

    Array[0] = (animal_t *)DogCtor();
    Array[1] = (animal_t *)CatCtor(NULL);
    Array[2] = (animal_t *)CatCtor("white");
    Array[3] = (animal_t *)LegendaryCtor(NULL);
    Array[4] = AnimalCtor(NULL);

    for (i = 0; i < 5; ++i)
    {
        ((object_t *)Array[i])->metadata->vtable[SAY_HELLO](Array[i]);
        printf("%d\n",Array[i]->num_masters);
    }

    for (i = 0; i < 5; ++i)
    {
        foo(Array[i]);
    }

    free(obj);
    free(Array[0]);
    free(Array[1]);
    free(Array[2]);
    free(Array[3]);
    free(Array[4]);
    free(animal);
    free(dog);
    free(cat);
    free(legend);
    
    printf("After gc");

    return (0);
    
}

static void foo(animal_t *animal)
{
    char *to_print = (char *)((object_t *)animal)->metadata->vtable[TOSTRING](animal);

    printf("%s\n", to_print);

    free(to_print);
}
/*==============================Ctor & Init funcs=============================*/
/*Object*/
object_t *ObjectCtor()
{   
    object_t *new_obj = (object_t *)malloc(sizeof(object_t));
    if (NULL == new_obj)
    {
        return (NULL);
    }

    new_obj->metadata = (class_t *)&ObjClass;

    return (new_obj);
}
/******************************************************************************/

/*Animal*/
animal_t *AnimalCtor(void *args)
{
    animal_t *new_animal = (animal_t *)malloc(sizeof(animal_t));
    if (NULL == new_animal)
    {
        return (NULL);
    }

    new_animal->parent.metadata = (class_t *)&AnimalClass;

    Animal_StaticBlockOne();
    Animal_StaticBlockTwo();
    
    if (NULL == args)
    {  
        Animal_NoArgsInit(new_animal);
    }
    else 
    {       
        Animal_ArgsInit(new_animal, *(int *)args);
    }

    return (new_animal);
}

void Animal_NoArgsInit(animal_t *animal_to_init)
{
    char *animal_print = NULL; 
    void *object_print = NULL;

    assert(NULL != animal_to_init);

    animal_to_init->num_legs = 5;
    animal_to_init->num_masters = 1;
    Animal_InstanceBlock();
    printf("Animal Ctor\n");
    animal_to_init->ID = ++(counter);
    (((object_t *)animal_to_init)->metadata->vtable[SAY_HELLO](animal_to_init));
   Animal_ShowCounter(animal_to_init);

    animal_print = (char *)(animal_to_init->parent.metadata->vtable[TOSTRING](animal_to_init)); 
    object_print = (char *)((object_t *)animal_to_init)->metadata->vtable[TOSTRING](animal_to_init);

    printf("%s\n",animal_print);
    printf("%p\n",object_print);

    free(animal_print);
    free(object_print);
}

void Animal_ArgsInit(animal_t *animal_to_init, int num_masters)
{
    assert(NULL != animal_to_init);

    animal_to_init->num_legs = 5;
    Animal_InstanceBlock();
    printf("Animal Ctor int\n");
    animal_to_init->ID = ++(counter);
    animal_to_init->num_masters = num_masters;
}

void Animal_StaticBlockOne()
{
    static int flag = FALSE;

    if (!flag)
    {
        printf("Static block Animal 1\n");
        flag = TRUE;
    }

    return;
}

void Animal_StaticBlockTwo()
{
    static int flag = FALSE;

    if (!flag)
    {
        printf("Static block Animal 2\n");
        flag = TRUE;
    }

    return;
}

void Animal_InstanceBlock()
{
    printf("Instance initialization block Animal\n");

    return;
}
/******************************************************************************/
/*Dog*/
dog_t *DogCtor(void)
{
    dog_t *new_dog = (dog_t *)malloc(sizeof(dog_t));
    if (NULL == new_dog)
    {
        return (NULL);
    }

    ((object_t *)new_dog)->metadata = (class_t *)&DogClass;

    Dog_StaticBlock();
    Dog_Init(new_dog);
    Dog_InstanceBlock();
    printf("Dog Ctor\n");

    return (new_dog);
}

void Dog_Init(dog_t *dog_to_init)
{
    assert(NULL != dog_to_init);

    dog_to_init->num_legs = 4; 

    Animal_ArgsInit((animal_t *)dog_to_init, 2);  
}

void Dog_StaticBlock()
{
    static int flag = FALSE;

    if (!flag)
    {
        printf("Static block Dog\n");
        flag = TRUE;
    }

    return;
}

void Dog_InstanceBlock()
{
    printf("Instance initialization block Dog\n");
   
    return;
}
/******************************************************************************/
/*Cat*/
cat_t *CatCtor(void *args)
{
    cat_t *new_cat = (cat_t *)malloc(sizeof(cat_t));
    if (NULL == new_cat)
    {
        return (NULL);
    }

    ((object_t *)new_cat)->metadata = (class_t *)&CatClass;

    Cat_StaticBlock();

    Animal_NoArgsInit((animal_t *)new_cat);

    if (NULL == args)
    {
        Cat_InitNoArgs(new_cat);
    }
    else
    {
        Cat_InitArgs(new_cat, args);
    }

    return (new_cat);
}

void Cat_InitNoArgs(cat_t *cat_to_init)
{
    assert(NULL != cat_to_init);
    Cat_InitArgs(cat_to_init, "black");

    cat_to_init->num_masters = 2; 
    
    printf("Cat Ctor\n"); 
}

void Cat_InitArgs(cat_t *cat_to_init, void *args)
{
    assert(NULL != cat_to_init);

    cat_to_init->colors = (char *)args;

    printf("Cat Ctor with color: %s\n", cat_to_init->colors);
 
}

void Cat_StaticBlock()
{
    static int flag = FALSE;

    if (!flag)
    {
        printf("Static block Cat\n");
        flag = TRUE;
    }

    return;
}

/******************************************************************************/
/*Legendary*/
legendary_animal_t *LegendaryCtor()
{
    legendary_animal_t *new_legendary = (legendary_animal_t *)malloc(sizeof(legendary_animal_t));
    if (NULL == new_legendary)
    {
        return (NULL);
    }

    ((object_t *)new_legendary)->metadata = (class_t *)&LegendaryClass;

    Legendary_StaticBlock();

    Animal_NoArgsInit(&(new_legendary->parent.parent));
    Cat_InitNoArgs(&(new_legendary->parent));

    printf("Legendary Ctor\n");

    return (new_legendary);
}

void Legendary_StaticBlock()
{
    static int flag = FALSE;

    if (!flag)
    {
        printf("Static block Legendary Animal\n");
        flag = TRUE;
    }

    return;
}

/*==============================Object funcs==================================*/
void *Obj_ToString(void *this)
{   
    assert(NULL != this);

    return (size_t *)(this);
}

void *Obj_Finalize(void *this)
{   
    assert(NULL != this);

    free((object_t *)this);

    return (NULL);
}

/*==============================Animal funcs==================================*/
void *Animal_ToString(void *this)
{   
    size_t string_len = strlen("Animal with ID: $");
    char *string = NULL;

    assert(NULL != this);

    string = (char *)malloc(string_len + 2);
    sprintf(string,"Animal with ID: %d", ((animal_t *)this)->ID);

    return (string);
}

void *Animal_SayHello(void *this)
{   
    assert(NULL != this);

    printf("Animal Hello!\n");
    printf("I have %d legs\n", ((animal_t *)this)->num_legs);

    return (NULL);
}

void *Animal_ShowCounter(void *this)
{   
    printf("%d\n", counter);

    return (NULL);
    (void)this;
}

void *Animal_GetNumMasters(void *this)
{   
    assert(NULL != this);

    return (&((animal_t *)this)->num_legs);
}

void *Animal_Finalize(void *this)
{   
    assert(NULL != this);

    printf("finalize Animal with ID: %d\n", ((animal_t *)this)->ID);

    free((((object_t *)this)->metadata->vtable[FINALIZE](this)));

    return (NULL);
}
/*==============================Dog funcs=====================================*/
void *Dog_ToString(void *this)
{   
    size_t string_len = strlen("Dog with ID: $");
    char *string = NULL;

    assert(NULL != this);

    string = (char *)malloc(string_len + 2);
    sprintf(string,"Dog with ID: %d", ((animal_t *)this)->ID);

    return (string);
}

void *Dog_SayHello(void *this)
{   
    assert(NULL != this);

    printf("Dog Hello!\n");
    printf("I have %d legs\n", ((dog_t *)this)->num_legs);

    return (NULL);
}

void *Dog_Finalize(void *this)
{   
    assert(NULL != this);

    printf("finalize Dog with ID: %d", ((animal_t *)this)->ID);

    free(this);

    return (NULL);
}

/*=============================Cat Funcs======================================*/
void *Cat_ToString(void *this)
{   
    size_t string_len = strlen("Cat with ID: $");
    char *string = NULL;

    assert(NULL != this);

    string = (char *)malloc(string_len + 2);
    sprintf(string,"Cat with ID: %d", ((animal_t *)this)->ID);

    return (string);
}

void *Cat_Finalize(void *this)
{   
    assert(NULL != this);

    printf("finalize Cat with ID: %d", ((animal_t *)this)->ID);

    free((((object_t *)this)->metadata->vtable[FINALIZE](this)));

    return (NULL);
}

/*=============================Legendary Funcs================================*/
void *LegendaryAnimal_ToString(void *this)
{   
    size_t string_len = strlen("LegendaryAnimal with ID: $");
    char *string = NULL;

    assert(NULL != this);

    string = (char *)malloc(string_len + 2);
    sprintf(string,"LegendaryAnimal with ID: %d", ((animal_t *)this)->ID);

    return (string);
}

void *LegendaryAnimal_SayHello(void *this)
{
    printf("Legendary Hello!\n");
    
    return (NULL);
    (void)this;
}

void *LegendaryAnimal_Finalize(void *this)
{   
    assert(NULL != this);

    printf("finalize LegendaryAnimal with ID: %d", ((animal_t *)this)->ID);

    free((((object_t *)this)->metadata->vtable[FINALIZE](this)));

    return (NULL);
}

