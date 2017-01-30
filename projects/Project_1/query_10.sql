SELECT  Distinct Suppliers.CompanyName
From Suppliers, Products
WHERE Suppliers.SupplierID = Products.SupplierID
AND Products.UnitsOnOrder >= 100