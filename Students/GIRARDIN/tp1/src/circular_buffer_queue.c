struct Queue *queue_init(size_t elem_size, size_t capacity){

    Queue q = {0, 0, capacity, elem_size, nullptr};
    return &q;
}

//-------------------------------------------------------------------------------
void queue_enqueue(struct Queue *q, const void *src){

    memcpy((q->data)[(q->front + q->length)%q->capacity], *src, *q.elem_size);
    q->length += 1;
    q->front = (q->front + q->length)%q->capacity;

}

//-------------------------------------------------------------------------------
void queue_dequeue(struct Queue *q, void *dest){
    if(q->length != 0){
        memcpy(*dest, *q.(*data)[q->front], *q.elem_size);
        q->front = (q->front + 1) % q->capacity;
        q->length -= 1;
    }
}

//-------------------------------------------------------------------------------
static void enlarge_queue_capacity(struct Queue *q){

    void *tmp = malloc(q->capacity * 2);
    memcpy(*tmp, q->data[((q->front + q-> length)%q->capacity)*q->elem_size], (q->elem_size)*(q->length)); 
    q->data = *tmp;
    q->capacity *= 2;

}