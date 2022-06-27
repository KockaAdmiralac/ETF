package rs.etf.iep.mapreduce;

import java.io.File;
import java.util.LinkedList;
import java.util.List;

import org.apache.commons.io.FileUtils;
import org.apache.hadoop.conf.Configuration;
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

public class Ocene2 {
	public static final int DEFAULT_N = 1;
	
	public static class Map1 extends Mapper<LongWritable, Text, Text, Text> {
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
					context.write(new Text(examSplit[0]), new Text(examSplit[2] + "\t1"));
				}
			} catch (Exception e) {
				// Хватају се све грешке јер Hadoop понекад може да их не испише.
				e.printStackTrace();
			}
		}
	}

	public static class Reduce1 extends Reducer<Text, Text, Text, Text> {
		@Override
		public void reduce(Text key, Iterable<Text> values, Context context) {
			try {
				int sum = 0;
				int count = 0;
				for (Text value : values) {
					String[] valueSplit = value.toString().split("\t");
					sum += Integer.parseInt(valueSplit[0]);
					count += Integer.parseInt(valueSplit[1]);
				}
				context.write(key, new Text(sum + "\t" + count));
			} catch (Exception e) {
				// Хватају се све грешке јер Hadoop понекад може да их не испише.
				e.printStackTrace();
			}
		}
	}

	public static void job1(String[] args) throws Exception {
		Job job = Job.getInstance();
		job.setJarByClass(Ocene2.class);
		job.setJobName("ocene2-1");

		job.setInputFormatClass(TextInputFormat.class);
		job.setOutputFormatClass(TextOutputFormat.class);

		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(Text.class);

		job.setMapperClass(Map1.class);
		job.setReducerClass(Reduce1.class);
		job.setCombinerClass(Reduce1.class);

		FileInputFormat.setInputPaths(job, new Path(args[0]));
		FileOutputFormat.setOutputPath(job, new Path("ocene2-temp"));

		job.waitForCompletion(true);
	}
	
	public static class Map2 extends Mapper<LongWritable, Text, Text, Text> {
		private static final Text text = new Text("ocene2-text");
		private int N;

		@Override
		public void setup(Context context) {
			N = context.getConfiguration().getInt("N", DEFAULT_N);
		}

		@Override
		public void map(LongWritable key, Text value, Context context) {
			try {
				String[] splitValue = value.toString().split("\t");
				double sum = Double.parseDouble(splitValue[1]);
				double count = Double.parseDouble(splitValue[2]);
				if (count >= N) {
					context.write(text, new Text(splitValue[0] + "\t" + (sum / count)));
				}
			} catch (Exception e) {
				// Хватају се све грешке јер Hadoop понекад може да их не испише.
				e.printStackTrace();
			}
		}
	}

	public static class Reduce2 extends Reducer<Text, Text, Text, Text> {
		@Override
		public void reduce(Text key, Iterable<Text> values, Context context) {
			try {
				double maxAvg = 0;
				List<String> list = new LinkedList<>();
				for (Text value : values) {
					String[] valueSplit = value.toString().split("\t");
					double avg = Double.parseDouble(valueSplit[1]);
					if (avg > maxAvg) {
						list.clear();
						maxAvg = avg;
					}
					if (avg == maxAvg) {
						list.add(value.toString());
					}
				}
				for (String value : list) {
					context.write(key, new Text(value));
				}
			} catch (Exception e) {
				// Хватају се све грешке јер Hadoop понекад може да их не испише.
				e.printStackTrace();
			}
		}
	}

	public static void job2(String[] args) throws Exception {
		Configuration conf = new Configuration();
		conf.setInt("N", Integer.parseInt(args[2]));

		Job job = Job.getInstance(conf, "ocene2-2");
		job.setJarByClass(Ocene2.class);

		job.setInputFormatClass(TextInputFormat.class);
		job.setOutputFormatClass(TextOutputFormat.class);

		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(Text.class);

		job.setMapperClass(Map2.class);
		job.setReducerClass(Reduce2.class);

		FileInputFormat.setInputPaths(job, new Path("ocene2-temp"));
		FileOutputFormat.setOutputPath(job, new Path(args[1]));

		job.waitForCompletion(true);
	}
	
	public static void main(String[] args) throws Exception {
		FileUtils.deleteDirectory(new File(args[1]));
		FileUtils.deleteDirectory(new File("ocene2-temp"));
		job1(args);
		job2(args);
	}
}
