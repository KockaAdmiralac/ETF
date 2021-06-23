using System;
using System.IO.Ports;
using System.Windows.Forms;

namespace ODE
{
    public partial class mainForm : Form
    {
        char[] buffer = new char[5];
        int bufferIndex = 0;

        public mainForm()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            refreshPorts_Click(sender, e);
        }

        private void refreshPorts_Click(object sender, EventArgs e)
        {
            portComboBox.Items.Clear();
            portComboBox.Items.AddRange(SerialPort.GetPortNames());
            if (portComboBox.Items.Count > 0)
            {
                portComboBox.SelectedIndex = 0;
            }
        }

        private void voltageSelect_ValueChanged(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                serialPort.Write(voltageSelect.Value.ToString("0.00"));
                serialPort.Write(new byte[] { 0 }, 0, 1);
            }
        }

        private void portComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            serialPort.Close();
            serialPort.PortName = (string) portComboBox.SelectedItem;
            serialPort.Open();
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            while (serialPort.IsOpen && serialPort.BytesToRead > 0)
            {
                buffer[bufferIndex++] = (char)serialPort.ReadByte();
                if (buffer[bufferIndex-1] == 'V')
                {
                    if (bufferIndex == 5)
                    {
                        voltageOutput.Text = new string(buffer);
                    }
                    bufferIndex = 0;
                }
            }
        }

        private void mainForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            serialPort.Close();
        }
    }
}
