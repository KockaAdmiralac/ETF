package rs.etf.iep.mapreduce;

import java.io.File;

import org.apache.commons.io.FileUtils;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;

public class Ocene1 {
	public static class Map extends Mapper<LongWritable, Text, Text, Text> {
		@Override
		public void map(LongWritable key, Text value, Context context) {
			try {
				String[] split = value.toString().split("\t");
				if (split.length <= 1) {
					// Студент нема ниједан испит.
					return;
				}
				for (String exam : split[1].split(";")) {
					String[] examSplit = exam.split(",");
					String examCode = examSplit[0];
					String examName = examSplit[1];
					int grade = Integer.parseInt(examSplit[2]);
					int[] gradeSplit = new int[5];
					gradeSplit[grade - 6] = 1;
					StringBuilder sb = new StringBuilder();
					sb.append(1);
					for (int i = 0; i < 5; ++i) {
						sb.append("\t");
						sb.append(gradeSplit[i]);
					}
					context.write(new Text(examCode + "\t" + examName), new Text(sb.toString()));
				}
			} catch (Exception e) {
				// Хватају се све грешке јер Hadoop понекад може да их не испише.
				e.printStackTrace();
			}
		}
	}

	public static class Reduce extends Reducer<Text, Text, Text, Text> {
		@Override
		public void reduce(Text key, Iterable<Text> values, Context context) {
			try {
				int studentCount = 0;
				int[] grades = new int[5];
				for (Text value : values) {
					String[] valueSplit = value.toString().split("\t");
					studentCount += Integer.parseInt(valueSplit[0]);
					for (int i = 0; i < 5; ++i) {
						grades[i] += Integer.parseInt(valueSplit[i + 1]);
					}
				}
				StringBuilder sb = new StringBuilder();
				sb.append(studentCount);
				for (int i = 0; i < 5; ++i) {
					sb.append("\t");
					sb.append(grades[i]);
				}
				context.write(key, new Text(sb.toString()));
			} catch (Exception e) {
				// Хватају се све грешке јер Hadoop понекад може да их не испише.
				e.printStackTrace();
			}
		}
	}

	public static void main(String[] args) throws Exception {
		FileUtils.deleteDirectory(new File(args[1]));

		Job job = Job.getInstance();
		job.setJarByClass(Ocene1.class);
		job.setJobName("ocene1");

		job.setInputFormatClass(TextInputFormat.class);
		job.setOutputFormatClass(TextOutputFormat.class);

		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(Text.class);

		job.setMapperClass(Map.class);
		job.setReducerClass(Reduce.class);
		job.setCombinerClass(Reduce.class);

		FileInputFormat.setInputPaths(job, new Path(args[0]));
		FileOutputFormat.setOutputPath(job, new Path(args[1]));

		job.waitForCompletion(true);
	}
}
