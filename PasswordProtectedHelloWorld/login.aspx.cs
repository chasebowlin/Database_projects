using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data.SqlClient;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class login : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        //nothing to do on page load
    }

    protected void loginButton_Click(object sender, EventArgs e)
    {
        //empty the error label if it has anything in it
        errorLabel.Text = "";

        //1. create a connection to the database
        SqlConnection dbConn = new SqlConnection();

        //1.1 set the connection string to a specific database
        dbConn.ConnectionString = ConfigurationManager.ConnectionStrings["UsersConnectionString"].ConnectionString;

        //2. create a command to tell the db what to do
        SqlCommand command = new SqlCommand();

        //2.1 set the name of the stored proc to call
        command.CommandText = "Login";
        command.CommandType = System.Data.CommandType.StoredProcedure;
        //associate the command with the connection
        command.Connection = dbConn;

        //set the parameters
        SqlParameter userNameParam = new SqlParameter();
        userNameParam.ParameterName = "@userName";
        userNameParam.Value = userNameTB.Text;
        userNameParam.SqlDbType = System.Data.SqlDbType.NVarChar;
        userNameParam.Size = 50;

        SqlParameter passwordParam = new SqlParameter();
        passwordParam.ParameterName = "@userPassword";
        passwordParam.Value = passwordTB.Text;
        passwordParam.SqlDbType = System.Data.SqlDbType.NVarChar;
        passwordParam.Size = 50;

        //add the parameters
        command.Parameters.Add(userNameParam);
        command.Parameters.Add(passwordParam);

        //3. open the connection
        dbConn.Open();

        //4. execute the query
        SqlDataReader reader = command.ExecuteReader();

        //if there are any rows then the login info was good
        if(reader.HasRows)
        {
            Session["loggedIn"] = true;
        }
        else //bad login info
        {
            Session["loggedIn"] = false;
        }

        //5. clean up all the resources
        command.Dispose();
        dbConn.Close();
        dbConn.Dispose();

        //if the login was successful
        if((bool)Session["loggedIn"] == true)
        {
            //go to the hello world page
            Response.Redirect("~/helloworld.aspx");
        }
        else //unsuccessful login
        {
            //display an error message
            errorLabel.Text = "Invalid Login";
        }
    }
}