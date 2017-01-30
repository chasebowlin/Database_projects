SELECT DISTINCT Products.ProductName
FROM Orders, [Order Details], Products, Customers
WHERE Orders.CustomerID = "THEBI"
AND Customers.CompanyName = "The Big Cheese"
AND Customers.CustomerID = Orders.CustomerID
AND Orders.OrderID = [Order Details].OrderID
AND [Order Details].ProductID = Products.ProductID
AND [Order Details].Quantity >= 10