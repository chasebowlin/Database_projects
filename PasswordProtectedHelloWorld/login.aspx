<%@ Page Language="C#" AutoEventWireup="true" CodeFile="login.aspx.cs" Inherits="login" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
        User name:<asp:TextBox ID="userNameTB" runat="server"></asp:TextBox>
        <br />
        Password:<asp:TextBox ID="passwordTB" runat="server" TextMode="Password"></asp:TextBox>
        <br />
        <asp:Button ID="loginButton" runat="server" OnClick="loginButton_Click" Text="Log in" />
        <br />
        <asp:Label ID="errorLabel" runat="server"></asp:Label>
    
    </div>
    </form>
</body>
</html>
