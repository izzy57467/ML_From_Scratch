# ML_From_Scratch

Jack Asaad - netID

Isabelle Villegas - iav180000

## Overview
We have created two programs that would model results from a Logistic Regression and Naïve Bayes model. Each model uses the data from titanic.csv to predict the survival rate using either sex or multiple predictors.

## Logistic Regression Results

## Naïve Bayes Results

## Generative Modifiers vs. Discriminative Modifiers
Discriminative Modifiers, which is associated with Logisitc Regression, will directly estimate the parameters of P(Y|X). Discriminative models are typically more efficient than generative models however. In regard to modifers though, the larger the data set becomes and the closer it gets to infinity the more similar the modifiers of both generative and discriminative become.

Generative Modifiers, opposingly is associated with Naïve Bayes and directly estimates the parameters of P(Y) and P(X|Y). Naïve Bayes, focuses essentially on the distribution of individual classes. If there is an outlier in the data set though, this will affect the accuracy of the model more so than a discriminative model. Naïve Bayes models do well with smaller data sets as opposed to the logisitc regression model, which gets better the bigger the data set gets.

## Reproducible Research in Machine Learning
Essentially, being reproducible in research in Machine Learning means being able to mimic a machine learning workflow in order to reach the same conclusion of the orignal work. It is incredibly crucial that each part of the machine learning process is well documented from the research in order for it to be replicated and replicated well lest it come to the wrong conclusion on different data. It is also important to be able to document well the machine learning process so that others can verify the same work to make sure that it was done well and that there were no errors in getting the results.

Several factors that stop research from being reproduced well can be hardware, computational power, training data, and smaller details like fine-tuning and new algorithm adopting. Joelle Pineau, a professor at McGill University, developed some methods that someone could use in order to make their research more reproducible such as having:

    1. Clear description of Algorithm along with the complexity analysis
    2. Links to data and dependencies
    3. Description of data collection process and how samples were allocated (training, testing, and validation)
    4. Methods used and results of those methods
    5. Details on computing infrastrucure

[Machine Learning Source 1](https://towardsdatascience.com/reproducible-machine-learning-cf1841606805)

[Machine Learning Source 2](https://blog.ml.cmu.edu/2020/08/31/5-reproducibility/)

[Modifiers Source](https://www.analyticsvidhya.com/blog/2021/07/deep-understanding-of-discriminative-and-generative-models-in-machine-learning/#h2_5)
