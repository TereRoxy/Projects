import pandas as pd
import numpy as np
import sklearn.preprocessing as skp

# Load the data
data = pd.read_csv("WA_Fn-UseC_-Telco-Customer-Churn.csv")

# drop the customerID column
data = data.drop(columns=['customerID'])

# Convert TotalCharges to numeric, coercing errors to NaN
data['TotalCharges'] = pd.to_numeric(data['TotalCharges'], errors='coerce')

# Fill NaN values in TotalCharges with 0 (or you can use data['TotalCharges'].mean())
data['TotalCharges'] = data['TotalCharges'].mean()

# Transform the categorical features in numeric integer labels using OrdinalEncoder
enc = skp.OrdinalEncoder()
data[data.select_dtypes(include=['object']).columns] = enc.fit_transform(data.select_dtypes(include=['object']))

# Scale the numerical data
scaler = skp.StandardScaler()
data[['tenure', 'MonthlyCharges', 'TotalCharges']] = scaler.fit_transform(data[['tenure', 'MonthlyCharges', 'TotalCharges']])

print(data)

# scale the numerical data and transform the categorical features in numeric integer labels
# customerID, gender, SeniorCitizen, Partner, Dependents, tenure,
# PhoneService, MultipleLines, InternetService, OnlineSecurity,
# OnlineBackup, DeviceProtection, TechSupport, StreamingTV, StreamingMovies,
# Contract, PaperlessBilling, PaymentMethod, MonthlyCharges, TotalCharges, Churn
