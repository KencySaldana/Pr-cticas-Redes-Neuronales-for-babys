"""
Import the Iris dataset and default classifier
Later in this course you will learn how to create your own dataset and classifier, 
but for now just use some defaults.
"""
from everywhereml.get_started import iris_dataset, iris_classifier
"""
First things first: print the contents of the Iris dataset.
(If you're familiar with pandas, .df gives you access to the 
underlying DataFrame object for the dataset.
You can call any DataFrame method on it.)
"""
iris_dataset.df
"""
Print some basic statistics about the Iris dataset
"""
iris_dataset.describe()

"""
Draw a pair-plot of the features.

The "setosa" class (blue) is clearly isolated from the other two: 
any classifier will be able to achieve 100% accuracy on it.

"versicolor" and "virginica", on the other hand, sometimes overlap: 
you can expect some classification errors between the two.
"""
iris_dataset.plot.features_pairplot()

"""
Fit classifier on Iris train dataset and test accuracy on Iris test dataset.
For such a simple dataset, you can expect a score above 0.9
"""
iris_train, iris_test = iris_dataset.split(test_size=0.3)
iris_classifier.fit(iris_train)

print('Classification score on test dataset: %.2f' % iris_classifier.score(iris_test))

"""
Export the classifier to Arduino C++ code.
"""
# return a string with the C++ code
iris_classifier.to_arduino(instance_name='classifier', class_map=iris_dataset.class_map)

# or save the contents directly to a file
print(iris_classifier.to_arduino_file(
    'sketches/IrisClassification/Classifier.h', 
    instance_name='classifier', 
    class_map=iris_dataset.class_map
))