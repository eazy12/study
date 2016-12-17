using System;
using Gtk;
using Npgsql;

namespace labwork
{
	public class MainClass
	{
		public MainWindow win;
		public DB_stuff dbstuff;
		public static void Main (string[] args)
		{			
			Application.Init ();
			MainWindow win = new MainWindow ();
			win.Show ();
			Application.Run ();
		}
	}
}
