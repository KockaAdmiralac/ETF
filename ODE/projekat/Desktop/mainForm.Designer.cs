
namespace ODE
{
    partial class mainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.Label label2;
            System.Windows.Forms.Label label1;
            System.Windows.Forms.Label label3;
            this.voltageSelect = new System.Windows.Forms.NumericUpDown();
            this.voltageOutput = new System.Windows.Forms.Label();
            this.portComboBox = new System.Windows.Forms.ComboBox();
            this.serialPort = new System.IO.Ports.SerialPort(this.components);
            this.refreshPorts = new System.Windows.Forms.Button();
            this.timer = new System.Windows.Forms.Timer(this.components);
            label2 = new System.Windows.Forms.Label();
            label1 = new System.Windows.Forms.Label();
            label3 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.voltageSelect)).BeginInit();
            this.SuspendLayout();
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new System.Drawing.Point(25, 15);
            label2.Name = "label2";
            label2.Size = new System.Drawing.Size(26, 13);
            label2.TabIndex = 3;
            label2.Text = "Port";
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new System.Drawing.Point(12, 41);
            label1.Name = "label1";
            label1.Size = new System.Drawing.Size(39, 13);
            label1.TabIndex = 4;
            label1.Text = "Napon";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new System.Drawing.Point(19, 62);
            label3.Name = "label3";
            label3.Size = new System.Drawing.Size(29, 13);
            label3.TabIndex = 5;
            label3.Text = "ADC";
            // 
            // voltageSelect
            // 
            this.voltageSelect.DecimalPlaces = 2;
            this.voltageSelect.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.voltageSelect.Location = new System.Drawing.Point(57, 39);
            this.voltageSelect.Maximum = new decimal(new int[] {
            500,
            0,
            0,
            131072});
            this.voltageSelect.Name = "voltageSelect";
            this.voltageSelect.Size = new System.Drawing.Size(120, 20);
            this.voltageSelect.TabIndex = 0;
            this.voltageSelect.ValueChanged += new System.EventHandler(this.voltageSelect_ValueChanged);
            // 
            // voltageOutput
            // 
            this.voltageOutput.AutoSize = true;
            this.voltageOutput.Location = new System.Drawing.Point(54, 62);
            this.voltageOutput.Name = "voltageOutput";
            this.voltageOutput.Size = new System.Drawing.Size(35, 13);
            this.voltageOutput.TabIndex = 1;
            this.voltageOutput.Text = "0.00V";
            this.voltageOutput.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // portComboBox
            // 
            this.portComboBox.FormattingEnabled = true;
            this.portComboBox.Location = new System.Drawing.Point(57, 12);
            this.portComboBox.Name = "portComboBox";
            this.portComboBox.Size = new System.Drawing.Size(84, 21);
            this.portComboBox.TabIndex = 2;
            this.portComboBox.SelectedIndexChanged += new System.EventHandler(this.portComboBox_SelectedIndexChanged);
            // 
            // refreshPorts
            // 
            this.refreshPorts.Location = new System.Drawing.Point(147, 10);
            this.refreshPorts.Name = "refreshPorts";
            this.refreshPorts.Size = new System.Drawing.Size(30, 23);
            this.refreshPorts.TabIndex = 6;
            this.refreshPorts.Text = "R";
            this.refreshPorts.UseVisualStyleBackColor = true;
            this.refreshPorts.Click += new System.EventHandler(this.refreshPorts_Click);
            // 
            // timer
            // 
            this.timer.Enabled = true;
            this.timer.Interval = 10;
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // mainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(187, 83);
            this.Controls.Add(this.refreshPorts);
            this.Controls.Add(label3);
            this.Controls.Add(label1);
            this.Controls.Add(label2);
            this.Controls.Add(this.portComboBox);
            this.Controls.Add(this.voltageOutput);
            this.Controls.Add(this.voltageSelect);
            this.Name = "mainForm";
            this.ShowIcon = false;
            this.Text = "ODE Projekat";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.mainForm_FormClosed);
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.voltageSelect)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.NumericUpDown voltageSelect;
        private System.Windows.Forms.Label voltageOutput;
        private System.Windows.Forms.ComboBox portComboBox;
        private System.IO.Ports.SerialPort serialPort;
        private System.Windows.Forms.Button refreshPorts;
        private System.Windows.Forms.Timer timer;
    }
}

