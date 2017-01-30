using System;
using System.Collections.Generic;
using System.Configuration; //to load config info from web.config
using System.Data.SqlClient; //for sql classes
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class admin : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        //nothing to do on page load
    }

    protected void createUserButton_Click(object sender, EventArgs e)
    {
        //get the new user name and password from the text boxes
        string userName = userNameTB.Text;
        string password = passwordTB.Text;

        //empty out the textboxes after we get the data from them
        userNameTB.Text = "";
        passwordTB.Text = "";

        //1. create a connection to the database
        SqlConnection dbConn = new SqlConnection();

        //1.1 set the connection string to a specific database
        dbConn.ConnectionString = ConfigurationManager.ConnectionStrings["UsersConnectionString"].ConnectionString;

        //2. create a command to tell the db what to do
        SqlCommand command = new SqlCommand();

        //2.1 set the text of the query to be sent with the command
        command.CommandText = "INSERT INTO UsersAndPasswords (userName, userPassword) VALUES (@userName, @userPassword)";
        //this will be a plain text query not a stored proc
        command.CommandType = System.Data.CommandType.Text;
        //associate the command with a connection
        command.Connection = dbConn;

        //2.2 fill in the parameters from the query 
        SqlParameter userNameParam = new SqlParameter();
        //the text that is being replaced in the query
        userNameParam.ParameterName = "@userName";
        //the value to replace it with
        userNameParam.Value = userName;
        //the type and size of the data
        userNameParam.SqlDbType = System.Data.SqlDbType.NVarChar;
        userNameParam.Size = 50;

        SqlParameter passwordParam = new SqlParameter();
        //the text that is being replaced in the query
        passwordParam.ParameterName = "@userPassword";
        //the value to replace it with
        passwordParam.Value = password;
        //the type and size of the data
        passwordParam.SqlDbType = System.Data.SqlDbType.NVarChar;
        passwordParam.Size = 50;

        //add the parameters to the command
        command.Parameters.Add(userNameParam);
        command.Parameters.Add(passwordParam);

        //3. open the connection to allow the command to go through it
        dbConn.Open();

        //4. execute the query (there are no results in an insert, use the non-query version)
        command.ExecuteNonQuery();

        //5. clean up all the resources
        command.Dispose();
        dbConn.Close();
        dbConn.Dispose();

        //since there is a new user, rebind the grid view to its data 
        //source (re-run the data source query and populate the grid view)
        GridView1.DataBind();
    }

    protected void allUserPasswordsButton_Click(object sender, EventArgs e)
    {
        //1. create a connection to the database
        SqlConnection dbConn = new SqlConnection();

        //1.1 set the connection string to a specific database
        dbConn.ConnectionString = ConfigurationManager.ConnectionStrings["UsersConnectionString"].ConnectionString;

        //2. create a command to tell the db what to do
        SqlCommand command = new SqlCommand();

        //2.1 set the name of the stored proc to be sent with the command
        command.CommandText = "AllPasswords";
        //stored proc not a text query
        command.CommandType = System.Data.CommandType.StoredProcedure;
        //associate the command with a connection
        command.Connection = dbConn;
        
        //3. open the connection
        dbConn.Open();

        //4. execute the query (this will produce some results)
        SqlDataReader reader = command.ExecuteReader();

        //used to find the average password length
        int totalLength = 0;
        int numPasswords = 0;
        float avgLength;

        //4.1 iterate through the results
        while (reader.Read()) //returns true as long as there are more rows
        {
            //get the column from the latest row 
            string password = (string)reader["userPassword"];
            //sum the length of the word
            totalLength += password.Length;
            numPasswords++;
        }

        //find the average length
        avgLength = (float)totalLength / (float)numPasswords;
        avgPasswordLengthLabel.Text = "The average length of the passwords is " + avgLength;

        //5. clean up all the resources
        command.Dispose();
        dbConn.Close();
        dbConn.Dispose();
    }
}