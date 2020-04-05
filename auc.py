import numpy as np 
from numba import jit
from sklearn.metrics import roc_auc_score  

# https://www.kaggle.com/c/microsoft-malware-prediction/discussion/76013
# https://www.ibm.com/developerworks/community/blogs/jfp/entry/Fast_Computation_of_AUC_ROC_score?lang=en
# AUC-ROC = | {(i,j), i in pos, j in neg, p(i) > p(j)} | / (| pos | x | neg |)
@jit
def fast_auc(y_true, y_prob):
    y_true = np.asarray(y_true)
    #把样本按照预测概率从小到大排序
    y_true = y_true[np.argsort(y_prob)]
    nfalse = 0
    auc = 0
    n = len(y_true)
    for i in range(n):
        y_i = y_true[i]
        #如果实际是正例，则此时的负例数nfalse就是|{(i,j),y_i是正例，y_j是负例}|的pair对数
        if y_i == 1:
            auc += y_i * nfalse
        else:
            nfalse += 1 
    auc /= (nfalse * (n - nfalse))
    return auc

def eval_auc(preds, dtrain):
    labels = dtrain.get_label()
    return 'auc', fast_auc(labels, preds), True

