# Simple loader script, loads the saved model from the notebook
# and predict the class from the choosen classifier 

from joblib import load
import sys 


# model file name 
filename = sys.argv[1]

# Load classifier
clf = load(filename)

# Get the strengths values 
vals = [float(i) for i in sys.argv[2:]]

# Print predicted class to console 
print(clf.predict([vals]))
