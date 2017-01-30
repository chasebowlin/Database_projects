<%@ Page Language="C#" AutoEventWireup="true" CodeFile="admin.aspx.cs" Inherits="admin" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
        All users<br />
        <asp:GridView ID="GridView1" runat="server" AllowPaging="True" AllowSorting="True" AutoGenerateColumns="False" CellPadding="4" DataSourceID="allUsersDataSource" ForeColor="#333333" GridLines="None">
            <AlternatingRowStyle BackColor="White" />
            <Columns>
                <asp:BoundField DataField="userName" HeaderText="userName" SortExpression="userName" />
            </Columns>
            <EditRowStyle BackColor="#2461BF" />
            <FooterStyle BackColor="#507CD1" ForeColor="White" Font-Bold="True" />
            <HeaderStyle BackColor="#507CD1" Font-Bold="True" ForeColor="White" />
            <PagerStyle ForeColor="White" HorizontalAlign="Center" BackColor="#2461BF" />
            <RowStyle BackColor="#EFF3FB" />
            <SelectedRowStyle BackColor="#D1DDF1" Font-Bold="True" ForeColor="#333333" />
            <SortedAscendingCellStyle BackColor="#F5F7FB" />
            <SortedAscendingHeaderStyle BackColor="#6D95E1" />
            <SortedDescendingCellStyle BackColor="#E9EBEF" />
            <SortedDescendingHeaderStyle BackColor="#4870BE" />
        </asp:GridView>
        <br />
        new user name <asp:TextBox ID="userNameTB" runat="server"></asp:TextBox>
        <br />
        new user password
        <asp:TextBox ID="passwordTB" runat="server"></asp:TextBox>
        <br />
        <asp:Button ID="createUserButton" runat="server" OnClick="createUserButton_Click" Text="Create a new user" />
    
        <br />
        <br />
        <asp:Button ID="allUserPasswordsButton" runat="server" OnClick="allUserPasswordsButton_Click" Text="Get the average password length" />
        <asp:Label ID="avgPasswordLengthLabel" runat="server"></asp:Label>
        <br />
    
    </div>
        <asp:SqlDataSource ID="allUsersDataSource" runat="server" ConnectionString="<%$ ConnectionStrings:UsersConnectionString %>" SelectCommand="SELECT [userName] FROM [UsersAndPasswords]"></asp:SqlDataSource>
    </form>
</body>
</html>
