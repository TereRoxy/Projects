import pandas as pd
import sklearn.model_selection as model_selection
import sklearn.linear_model as linear_model
import matplotlib.pyplot as plt

path = "archive/score.csv"
# Load the data
df = pd.read_csv(path)

# Display the first few rows of the dataframe
print(df.head())

# Split the data into features and target variable
X = df[['Hours']]
y = df['Scores']

# Split the data into training and test sets
X_train, X_test, y_train, y_test = model_selection.train_test_split(X, y, test_size=0.2, random_state=42)

# Train a linear regression model
model = linear_model.LinearRegression()
model.fit(X_train, y_train)

# Make predictions
y_pred = model.predict(X_test)

# Make 3 predictions
sample_hours = pd.DataFrame({'Hours': [2, 5, 9]})
sample_predictions = model.predict(sample_hours)
print("Predictions for sample hours:", sample_predictions)

# Plot the training set
plt.scatter(X_train, y_train, color='blue', label='Training data')
plt.plot(X_train, model.predict(X_train), color='red', label='Regression line')
plt.title('Training set')
plt.xlabel('Hours')
plt.ylabel('Scores')
plt.legend()
plt.show()

# Plot the test set
plt.scatter(X_test, y_test, color='green', label='Test data')
plt.plot(X_train, model.predict(X_train), color='red', label='Regression line')
plt.title('Test set')
plt.xlabel('Hours')
plt.ylabel('Scores')
plt.legend()
plt.show()

# Plot the predictions
plt.scatter(X_test, y_test, color='green', label='Test data')
plt.scatter(sample_hours, sample_predictions, color='orange', label='Predictions')
plt.plot(X_train, model.predict(X_train), color='red', label='Regression line')
plt.title('Predictions')
plt.xlabel('Hours')
plt.ylabel('Scores')
plt.legend()
plt.show()