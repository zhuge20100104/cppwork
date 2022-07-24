# 引用: https://blog.csdn.net/qq_39827677/article/details/119894878
import tensorflow as tf

def accuracy(output, target, topk=(1,)):
    # output [10,6]
    maxk = max(topk)
    batch_size = target.shape[0]
    
    pred = tf.math.top_k(output, maxk).indices # 前K个最大值的索引 [10,maxk]
#     print('每行top-6 最大值',tf.math.top_k(output, maxk).values)
    print('每行top-6 最大值下标',tf.math.top_k(output, maxk).indices)
    pred = tf.transpose(pred, perm=[1, 0]) # 转置 [maxk,10] 方便统计比较
    print('转置 每行top-6 最大值下标',pred)
    
    target_ = tf.broadcast_to(target, pred.shape) # target [10]广播成相同的形状 [maxk,10]
    print('准确值',target_)
    correct = tf.equal(pred, target_)
    print(correct)
    res = []
    for k in topk:
        # 分别计算top-1 到 top-k的准确率
        correct_k = tf.cast(tf.reshape(correct[:k], [-1]), dtype=tf.float32)
        # 展成行统计1的个数
        correct_k = tf.reduce_sum(correct_k)
        acc = float(correct_k* (100.0 / batch_size) )
        res.append(acc)

    return res


output = tf.random.normal([10, 6])
output = tf.math.softmax(output, axis=1)  # 使得每行概率之和为1
target = tf.random.uniform([10], maxval=6, dtype=tf.int32) # 生成6类样本 因此top-6准确率一定为100%
print('prob:', output.numpy())

pred = tf.argmax(output, axis=1) # argmax() 每行最大值的索引
print('pred:', pred.numpy())
print('label:', target.numpy())

acc = accuracy(output, target, topk=(1,2,3,4,5,6))
print('\ntop-1-6 acc:', acc)
