
// This file has been generated by the GUI designer. Do not modify.
namespace labwork
{
	public partial class deleteElement
	{
		private global::Gtk.VBox vbox7;
		
		private global::Gtk.ScrolledWindow GtkScrolledWindow;
		
		private global::Gtk.TextView textview1;
		
		private global::Gtk.HBox hbox3;
		
		private global::Gtk.ComboBoxEntry comboboxentry6;
		
		private global::Gtk.VPaned vpaned12;
		
		private global::Gtk.Button button6;
		
		private global::Gtk.Fixed fixed2;
		
		private global::Gtk.HBox hbox5;
		
		private global::Gtk.Button button8;
		
		private global::Gtk.HPaned hpaned5;
		
		private global::Gtk.Button button9;
		
		private global::Gtk.HBox hbox6;
		
		private global::Gtk.HPaned hpaned1;
		
		private global::Gtk.Label label2;
		
		private global::Gtk.HPaned hpaned2;
		
		private global::Gtk.Label label3;
		
		private global::Gtk.HPaned hpaned3;
		
		private global::Gtk.Label label4;
		
		private global::Gtk.HPaned hpaned4;
		
		private global::Gtk.Label label5;
		
		private global::Gtk.HBox hbox7;
		
		private global::Gtk.Entry entry1;
		
		private global::Gtk.Entry entry2;
		
		private global::Gtk.Entry entry3;
		
		private global::Gtk.Entry entry4;

		protected virtual void Build ()
		{
			global::Stetic.Gui.Initialize (this);
			// Widget labwork.deleteElement
			this.Name = "labwork.deleteElement";
			this.Title = global::Mono.Unix.Catalog.GetString ("deleteElement");
			this.WindowPosition = ((global::Gtk.WindowPosition)(4));
			// Container child labwork.deleteElement.Gtk.Container+ContainerChild
			this.vbox7 = new global::Gtk.VBox ();
			this.vbox7.Name = "vbox7";
			this.vbox7.Spacing = 6;
			// Container child vbox7.Gtk.Box+BoxChild
			this.GtkScrolledWindow = new global::Gtk.ScrolledWindow ();
			this.GtkScrolledWindow.Name = "GtkScrolledWindow";
			this.GtkScrolledWindow.ShadowType = ((global::Gtk.ShadowType)(1));
			// Container child GtkScrolledWindow.Gtk.Container+ContainerChild
			this.textview1 = new global::Gtk.TextView ();
			this.textview1.CanFocus = true;
			this.textview1.Name = "textview1";
			this.textview1.Editable = false;
			this.GtkScrolledWindow.Add (this.textview1);
			this.vbox7.Add (this.GtkScrolledWindow);
			global::Gtk.Box.BoxChild w2 = ((global::Gtk.Box.BoxChild)(this.vbox7 [this.GtkScrolledWindow]));
			w2.Position = 0;
			// Container child vbox7.Gtk.Box+BoxChild
			this.hbox3 = new global::Gtk.HBox ();
			this.hbox3.Name = "hbox3";
			this.hbox3.Spacing = 6;
			// Container child hbox3.Gtk.Box+BoxChild
			this.comboboxentry6 = global::Gtk.ComboBoxEntry.NewText ();
			this.comboboxentry6.Name = "comboboxentry6";
			this.hbox3.Add (this.comboboxentry6);
			global::Gtk.Box.BoxChild w3 = ((global::Gtk.Box.BoxChild)(this.hbox3 [this.comboboxentry6]));
			w3.Position = 0;
			w3.Expand = false;
			w3.Fill = false;
			// Container child hbox3.Gtk.Box+BoxChild
			this.vpaned12 = new global::Gtk.VPaned ();
			this.vpaned12.CanFocus = true;
			this.vpaned12.Name = "vpaned12";
			this.vpaned12.Position = 31;
			// Container child vpaned12.Gtk.Paned+PanedChild
			this.button6 = new global::Gtk.Button ();
			this.button6.CanFocus = true;
			this.button6.Name = "button6";
			this.button6.UseUnderline = true;
			this.button6.Label = global::Mono.Unix.Catalog.GetString ("Удалить");
			this.vpaned12.Add (this.button6);
			this.hbox3.Add (this.vpaned12);
			global::Gtk.Box.BoxChild w5 = ((global::Gtk.Box.BoxChild)(this.hbox3 [this.vpaned12]));
			w5.Position = 2;
			w5.Expand = false;
			w5.Fill = false;
			this.vbox7.Add (this.hbox3);
			global::Gtk.Box.BoxChild w6 = ((global::Gtk.Box.BoxChild)(this.vbox7 [this.hbox3]));
			w6.Position = 1;
			w6.Expand = false;
			w6.Fill = false;
			// Container child vbox7.Gtk.Box+BoxChild
			this.fixed2 = new global::Gtk.Fixed ();
			this.fixed2.Name = "fixed2";
			this.fixed2.HasWindow = false;
			this.vbox7.Add (this.fixed2);
			global::Gtk.Box.BoxChild w7 = ((global::Gtk.Box.BoxChild)(this.vbox7 [this.fixed2]));
			w7.Position = 2;
			w7.Expand = false;
			w7.Fill = false;
			// Container child vbox7.Gtk.Box+BoxChild
			this.hbox5 = new global::Gtk.HBox ();
			this.hbox5.Name = "hbox5";
			this.hbox5.Spacing = 6;
			// Container child hbox5.Gtk.Box+BoxChild
			this.button8 = new global::Gtk.Button ();
			this.button8.CanFocus = true;
			this.button8.Name = "button8";
			this.button8.UseUnderline = true;
			this.button8.Label = global::Mono.Unix.Catalog.GetString ("<-");
			this.hbox5.Add (this.button8);
			global::Gtk.Box.BoxChild w8 = ((global::Gtk.Box.BoxChild)(this.hbox5 [this.button8]));
			w8.Position = 0;
			w8.Expand = false;
			w8.Fill = false;
			// Container child hbox5.Gtk.Box+BoxChild
			this.hpaned5 = new global::Gtk.HPaned ();
			this.hpaned5.CanFocus = true;
			this.hpaned5.Name = "hpaned5";
			this.hpaned5.Position = 10;
			this.hbox5.Add (this.hpaned5);
			global::Gtk.Box.BoxChild w9 = ((global::Gtk.Box.BoxChild)(this.hbox5 [this.hpaned5]));
			w9.Position = 1;
			// Container child hbox5.Gtk.Box+BoxChild
			this.button9 = new global::Gtk.Button ();
			this.button9.CanFocus = true;
			this.button9.Name = "button9";
			this.button9.UseUnderline = true;
			this.button9.Label = global::Mono.Unix.Catalog.GetString ("->");
			this.hbox5.Add (this.button9);
			global::Gtk.Box.BoxChild w10 = ((global::Gtk.Box.BoxChild)(this.hbox5 [this.button9]));
			w10.Position = 2;
			w10.Expand = false;
			w10.Fill = false;
			this.vbox7.Add (this.hbox5);
			global::Gtk.Box.BoxChild w11 = ((global::Gtk.Box.BoxChild)(this.vbox7 [this.hbox5]));
			w11.Position = 3;
			w11.Expand = false;
			w11.Fill = false;
			// Container child vbox7.Gtk.Box+BoxChild
			this.hbox6 = new global::Gtk.HBox ();
			this.hbox6.Name = "hbox6";
			this.hbox6.Spacing = 6;
			// Container child hbox6.Gtk.Box+BoxChild
			this.hpaned1 = new global::Gtk.HPaned ();
			this.hpaned1.CanFocus = true;
			this.hpaned1.Name = "hpaned1";
			this.hpaned1.Position = 10;
			// Container child hpaned1.Gtk.Paned+PanedChild
			this.label2 = new global::Gtk.Label ();
			this.label2.Name = "label2";
			this.hpaned1.Add (this.label2);
			this.hbox6.Add (this.hpaned1);
			global::Gtk.Box.BoxChild w13 = ((global::Gtk.Box.BoxChild)(this.hbox6 [this.hpaned1]));
			w13.Position = 0;
			// Container child hbox6.Gtk.Box+BoxChild
			this.hpaned2 = new global::Gtk.HPaned ();
			this.hpaned2.CanFocus = true;
			this.hpaned2.Name = "hpaned2";
			this.hpaned2.Position = 10;
			// Container child hpaned2.Gtk.Paned+PanedChild
			this.label3 = new global::Gtk.Label ();
			this.label3.Name = "label3";
			this.hpaned2.Add (this.label3);
			this.hbox6.Add (this.hpaned2);
			global::Gtk.Box.BoxChild w15 = ((global::Gtk.Box.BoxChild)(this.hbox6 [this.hpaned2]));
			w15.Position = 1;
			// Container child hbox6.Gtk.Box+BoxChild
			this.hpaned3 = new global::Gtk.HPaned ();
			this.hpaned3.CanFocus = true;
			this.hpaned3.Name = "hpaned3";
			this.hpaned3.Position = 10;
			// Container child hpaned3.Gtk.Paned+PanedChild
			this.label4 = new global::Gtk.Label ();
			this.label4.Name = "label4";
			this.hpaned3.Add (this.label4);
			this.hbox6.Add (this.hpaned3);
			global::Gtk.Box.BoxChild w17 = ((global::Gtk.Box.BoxChild)(this.hbox6 [this.hpaned3]));
			w17.Position = 2;
			// Container child hbox6.Gtk.Box+BoxChild
			this.hpaned4 = new global::Gtk.HPaned ();
			this.hpaned4.CanFocus = true;
			this.hpaned4.Name = "hpaned4";
			this.hpaned4.Position = 10;
			// Container child hpaned4.Gtk.Paned+PanedChild
			this.label5 = new global::Gtk.Label ();
			this.label5.Name = "label5";
			this.hpaned4.Add (this.label5);
			this.hbox6.Add (this.hpaned4);
			global::Gtk.Box.BoxChild w19 = ((global::Gtk.Box.BoxChild)(this.hbox6 [this.hpaned4]));
			w19.Position = 3;
			this.vbox7.Add (this.hbox6);
			global::Gtk.Box.BoxChild w20 = ((global::Gtk.Box.BoxChild)(this.vbox7 [this.hbox6]));
			w20.Position = 4;
			// Container child vbox7.Gtk.Box+BoxChild
			this.hbox7 = new global::Gtk.HBox ();
			this.hbox7.Name = "hbox7";
			this.hbox7.Spacing = 6;
			// Container child hbox7.Gtk.Box+BoxChild
			this.entry1 = new global::Gtk.Entry ();
			this.entry1.CanFocus = true;
			this.entry1.Name = "entry1";
			this.entry1.IsEditable = true;
			this.entry1.InvisibleChar = '●';
			this.hbox7.Add (this.entry1);
			global::Gtk.Box.BoxChild w21 = ((global::Gtk.Box.BoxChild)(this.hbox7 [this.entry1]));
			w21.Position = 0;
			// Container child hbox7.Gtk.Box+BoxChild
			this.entry2 = new global::Gtk.Entry ();
			this.entry2.CanFocus = true;
			this.entry2.Name = "entry2";
			this.entry2.IsEditable = true;
			this.entry2.InvisibleChar = '●';
			this.hbox7.Add (this.entry2);
			global::Gtk.Box.BoxChild w22 = ((global::Gtk.Box.BoxChild)(this.hbox7 [this.entry2]));
			w22.Position = 1;
			// Container child hbox7.Gtk.Box+BoxChild
			this.entry3 = new global::Gtk.Entry ();
			this.entry3.CanFocus = true;
			this.entry3.Name = "entry3";
			this.entry3.IsEditable = true;
			this.entry3.InvisibleChar = '●';
			this.hbox7.Add (this.entry3);
			global::Gtk.Box.BoxChild w23 = ((global::Gtk.Box.BoxChild)(this.hbox7 [this.entry3]));
			w23.Position = 2;
			// Container child hbox7.Gtk.Box+BoxChild
			this.entry4 = new global::Gtk.Entry ();
			this.entry4.CanFocus = true;
			this.entry4.Name = "entry4";
			this.entry4.IsEditable = true;
			this.entry4.InvisibleChar = '●';
			this.hbox7.Add (this.entry4);
			global::Gtk.Box.BoxChild w24 = ((global::Gtk.Box.BoxChild)(this.hbox7 [this.entry4]));
			w24.Position = 3;
			this.vbox7.Add (this.hbox7);
			global::Gtk.Box.BoxChild w25 = ((global::Gtk.Box.BoxChild)(this.vbox7 [this.hbox7]));
			w25.Position = 5;
			w25.Expand = false;
			w25.Fill = false;
			this.Add (this.vbox7);
			if ((this.Child != null)) {
				this.Child.ShowAll ();
			}
			this.DefaultWidth = 682;
			this.DefaultHeight = 300;
			this.Show ();
			this.DeleteEvent += new global::Gtk.DeleteEventHandler (this.OnDeleteEvent);
			this.comboboxentry6.Changed += new global::System.EventHandler (this.OnComboboxentry6Changed);
			this.button6.Clicked += new global::System.EventHandler (this.OnButton6Clicked);
		}
	}
}
