using System;
using Gtk;
using Npgsql;

namespace labwork
{
	public partial class deleteElement : Gtk.Window
	{
		string dest, field0, field1,field2,field3;
		DB_stuff dbstuff = new DB_stuff("Server=localhost;Port=5432;User Id=just_user;Password=QWERTY;Database=just_test;");
		public deleteElement () :
			base (Gtk.WindowType.Toplevel)
		{
			this.Build ();
			comboboxentry6.Clear ();
			CellRendererText cell = new CellRendererText();
			comboboxentry6.PackStart(cell, false);
			comboboxentry6.AddAttribute(cell, "text", 0);
			ListStore store = new ListStore(typeof (string));
			comboboxentry6.Model = store;
			store.AppendValues ("Студенты");
			store.AppendValues ("Экзамены");
			store.AppendValues ("Результаты");

		}

		protected void OnComboboxentry6Changed (object sender, EventArgs e)
		{
			
			string r = comboboxentry6.ActiveText;

			if (r == "Студенты") {
				label5.Text = "На отчисление";
				label4.Text = "ФИО";
				label3.Text = "Номер зачетки";
				label2.Text = "Номер группы";
			} else if (r == "Экзамены") {
				label5.Text = "Преподователь";
				label4.Text = "Предмет";
				label3.Text = "Номер экзамена";
				label2.Text = "Дата сдачи";
			} else if (r == "Результаты") {
				label5.Text = "Оценка";
				label4.Text = "Номер зачетки";
				label3.Text = "Номер экзамена";
				label2.Text = "Дата сдачи";
			}
			if (r == "Студенты") {
				dest = "students";
				field0 = "expelling";
				field1 = "fio";
				field2 = "studcard_number";
				field3 = "group_number";
				dbstuff.setCommand = " select group_number studcard_number, fio from students;";
			} else if (r == "Экзамены") {
				dest = "exams";
				field0 = "lector_name";
				field1 = "exam_name";
				field2 = "exam_number";
				field3 = "pass_time";
				dbstuff.setCommand = "select  to_char(pass_time, 'DD/MM/YYYY') , exam_number, , exam_name, lector_name from exams;";
			} else if (r == "Результаты") {
				dest = "exams_taking";
				field0 = "mark";
				field1 = "studcard_number";
				field2 = "exam_number";
				field3 = "pass_time";
				dbstuff.setCommand = " select to_char(pass_time, 'DD/MM/YYYY'), exam_number, studcard_number, mark from exams_taking;";
			}
			NpgsqlDataReader reader;

			dbstuff.conn.Open();


			reader =  dbstuff.comm.ExecuteReader();
			textview1.Buffer.Text = "";
			while (reader.Read ()) {
				for (int i = 0; i < reader.FieldCount; i++) {
					textview1.Buffer.Text += reader.GetString(i) + "\t" + "\t" + "\t";
				}
				textview1.Buffer.Text += "\n";
			}


			Console.WriteLine (dbstuff.setCommand);

			dbstuff.conn.Close();
		}

		protected void OnDeleteEvent (object sender, DeleteEventArgs a)
		{
			this.Destroy ();
			SecondWindow win2 = new SecondWindow();
			win2.Show ();
		}
			

		protected void OnButton6Clicked (object sender, EventArgs e)
		{
			dbstuff.setCommand = "BEGIN; delete from" + dest + "where "+ field1 + " = " +
				entry2.Text + " and " + field2 + " = " + entry3.Text + " ); END;"; 

			NpgsqlDataReader reader;

			dbstuff.conn.Open();


			reader =  dbstuff.comm.ExecuteReader();

			dbstuff.conn.Close();
		}
	}
}

