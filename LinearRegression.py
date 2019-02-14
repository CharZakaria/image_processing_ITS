from sklearn.multioutput import MultiOutputRegressor
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error
from sklearn.model_selection import train_test_split
import pandas as pd 
import numpy as np

df=pd.read_csv("data_stat_all.csv")

train, test = train_test_split(df, test_size=0.2)

X=train.drop(columns = ['image','p1' , 'p2', 'p3', 'p4'])
Y=train[['p1' , 'p2', 'p3', 'p4']].copy()

X_test=test.drop(columns = ['image','p1' , 'p2', 'p3', 'p4'])
Y_test=test[['p1' , 'p2', 'p3', 'p4']].copy()
est= LinearRegression()
clf = MultiOutputRegressor(est)
clf.fit(X,Y)
# score = clf.score(X_test,Y_test)
Y_predict = clf.predict(X_test) 
score = mean_squared_error(Y_test,Y_predict, multioutput=[0.25,0.25,0.25,0.25])
print("multi output score : ",score)

reg=LinearRegression()
reg.fit(X,train['p1'])
y0 = reg.predict(X_test)
score1 = mean_squared_error(Y_test['p1'],y0)

re2=LinearRegression()
re2.fit(X,train['p2'])
y2 = re2.predict(X_test)
score2 = mean_squared_error(Y_test['p2'],y2)

re3=LinearRegression()
re3.fit(X,train['p3'])
y3 = re3.predict(X_test)
score3 = mean_squared_error(Y_test['p3'],y3)


re4=LinearRegression()
re4.fit(X,train['p4'])
y4 = re4.predict(X_test)
score4 = mean_squared_error(Y_test['p4'],y4)

score = [score1,score2,score3,score4]
print("final score : ",score)
