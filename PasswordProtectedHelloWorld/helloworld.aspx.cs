using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class helloworld : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        //super secret hello world page

        //if there is NOT a session OR it is null
        if(Session["loggedIn"] == null ||
           Convert.ToBoolean(Session["loggedIn"]) == false)
        {
            //send the user back to the login page
            Response.Redirect("~/login.aspx");
        }
    }

    protected void logOutButton_Click(object sender, EventArgs e)
    {
        //indicate that the user is not logged in anymore
        Session["loggedIn"] = false;

        //send them back to the login page
        Response.Redirect("login.aspx");
    }
}