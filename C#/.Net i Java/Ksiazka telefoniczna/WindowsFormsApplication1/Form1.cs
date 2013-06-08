using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;

namespace Lista_Kontaktow
{
    [Serializable]
    public partial class Lista_Kontaktów : Form
    {

        public Lista_Kontaktów()
        {
            InitializeComponent();
        }

        struct Telefon
        {
            public string numer;
            public string typ;
        }

        public int wiek(string Data_urodzenia)
        {
            try
            {
                DateTime Bday = new DateTime();
                Bday = DateTime.ParseExact(Data_urodzenia, "dd.MM.yyyy", null);
                DateTime now = DateTime.Today;
                int age = now.Year - Bday.Year;
                if (now < Bday.AddYears(age)) age--;
                    return age;
            }
            catch (Exception E)
            {
                MessageBox.Show("Błąd: " + E.Message, "Błąd", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return 0;
            }

        }

        BinaryFormatter f = new BinaryFormatter();

        private void button1_Click(object sender, EventArgs e)
        {
            int Data=wiek(Data_urodzenia.Text);

            ListViewItem nowy = new ListViewItem(Imie.Text);
            nowy.SubItems.Add(Nazwisko.Text);
            nowy.SubItems.Add(Data.ToString());
            nowy.SubItems.Add(Ulica.Text+" "+Nr.Text);
            nowy.SubItems.Add(kod.Text);
            nowy.SubItems.Add(Miasto.Text);
            nowy.SubItems.Add(Panstwo.Text);
            nowy.SubItems.Add(email.Text);
            nowy.SubItems.Add(www.Text);
                                      //telefon
            if (Data != 0)
            {
                listView1.Items.Add(nowy);

                Imie.Text = "";
                Nazwisko.Text = "";
                Data_urodzenia.Text = "";
                Ulica.Text = "";
                Nr.Text = "";
                kod.Text = "";
                Miasto.Text = "";
                Panstwo.Text = "";
                email.Text = "";
                www.Text = "";
                pictureBox1.Image = WindowsFormsApplication1.Properties.Resources.indeks;
            }


                                                         // zdjecie jest dodane "na luźno" trzeba je upakowac do klasy osoba ! (nie znajduje sie w klasie)
            //nowy.zdjecie 
            //int selectedIndex = listView1.
            //listView1.DataSource = null;
            //listView1.DataSource = Lista;                // dodanie nazw na liscie w okienku (nie wyswietla poprawnie)

            }
        
       private void d_zdjecie_Click_1(object sender, EventArgs e)
        {

            OpenFileDialog openfile1 = new OpenFileDialog();
            openfile1.ShowDialog();
            pictureBox1.ImageLocation = openfile1.FileName;
            this.Text = openfile1.FileName; 
            
        }
        
        private void button2_Click(object sender, EventArgs e)
        {
            if (listView1.SelectedItems.Count == 0) return;
            listView1.SelectedItems[0].Remove();
        }

        private void Form1_Load_1(object sender, EventArgs e)
        {
            try
            {
                //Stream file = File.Open("data.bin", FileMode.Open);
                //listView1 = (ListView)f.Deserialize(file); nie dziala... TEZ! :D
                //file.Close();
            }
            catch (Exception E)
            {
                MessageBox.Show("Błąd: " + E.Message, "Błąd", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void Form1_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            Stream file = File.Open("data.bin", FileMode.Create);
            f.Serialize(file, listView1);  // nie zapisuje :(
            file.Close();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            //UpdateListView
        }

        private void email_button_Click(object sender, EventArgs e)
        {
            Form3 f3 = new Form3();
            f3.show;
        }

    }
    
}