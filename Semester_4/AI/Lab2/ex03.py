import pandas as pd
import sklearn.model_selection as model_selection
import sklearn.linear_model as linear_model
import sklearn.preprocessing as preprocessing
import matplotlib.pyplot as plt

# Load the data
path = "archive/score_updated.csv"
df = pd.read_csv(path)

# Display the first few rows of the dataframe
print(df.head())

# Split the data into features and target variable
X = df[['Hours']]
y = df['Scores']

# Scaling: Standardize the numerical features
scaler = preprocessing.StandardScaler()
X_scaled = scaler.fit_transform(X)

# Split the data into training and test sets
X_train, X_test, y_train, y_test = model_selection.train_test_split(X_scaled, y, test_size=0.2, random_state=42)

# Reshape the data to have a two-dimensional array
X_train = X_train.reshape(-1, 1)
X_test = X_test.reshape(-1, 1)

# Train a linear regression model
model = linear_model.LinearRegression()
model.fit(X_train, y_train)

# Train a Ridge regression model (L2 regularization)
ridge = linear_model.Ridge(alpha=1.0)
ridge.fit(X_train, y_train)
print(f"Ridge-Training set score: {ridge.score(X_train, y_train):.2f}")
print(f"Ridge-Test set score: {ridge.score(X_test, y_test):.2f}")

# Train a Lasso regression model (L1 regularization)
lasso = linear_model.Lasso(alpha=0.1)
lasso.fit(X_train, y_train)
print(f"Lasso-Training set score: {lasso.score(X_train, y_train):.2f}")
print(f"Lasso-Test set score: {lasso.score(X_test, y_test):.2f}")

# Train an Elastic Net regression model
elastic_net = linear_model.ElasticNet(alpha=0.01, l1_ratio=0.5)
elastic_net.fit(X_train, y_train)
print(f"Elastic Net-Training set score: {elastic_net.score(X_train, y_train):.2f}")
print(f"Elastic Net-Test set score: {elastic_net.score(X_test, y_test):.2f}")

# Make 3 predictions using the Elastic Net model
sample_hours = pd.DataFrame({'Hours': [2, 5, 9]})
sample_hours_scaled = scaler.transform(sample_hours)
sample_hours_scaled = sample_hours_scaled.reshape(-1, 1)
sample_predictions = elastic_net.predict(sample_hours_scaled)
print("Predictions for sample hours:", sample_predictions)

# Plot the training set
plt.scatter(X_train, y_train, color='blue', label='Training data')
plt.plot(X_train, elastic_net.predict(X_train), color='red', label='Regression line')
plt.title('Training set')
plt.xlabel('Hours')
plt.ylabel('Scores')
plt.legend()
plt.show()

# Plot the test set
plt.scatter(X_test, y_test, color='green', label='Test data')
plt.plot(X_train, elastic_net.predict(X_train), color='red', label='Regression line')
plt.title('Test set')
plt.xlabel('Hours')
plt.ylabel('Scores')
plt.legend()
plt.show()

# Plot the predictions
plt.scatter(X_test, y_test, color='green', label='Test data')
plt.scatter(sample_hours_scaled, sample_predictions, color='orange', label='Predictions')
plt.plot(X_train, elastic_net.predict(X_train), color='red', label='Regression line')
plt.title('Predictions')
plt.xlabel('Hours')
plt.ylabel('Scores')
plt.legend()
plt.show()
