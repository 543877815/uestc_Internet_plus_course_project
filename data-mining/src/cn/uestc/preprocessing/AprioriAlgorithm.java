package cn.uestc.preprocessing;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.*;

public class AprioriAlgorithm {

    private Map<Integer, Set<String>> txDatabase; //事物数据库

    private Float minSup; //最小支持度
    private Float minConf; //最小置信度
    private Integer txDatabaseCount; //事物数据库中的事务数

    private static Map<Integer, Set<Set<String>>> freqItemSet; // 频繁项集集合
    private static Map<Integer, Map<Set<String>, Float>> freqItemSets; //所有频繁项集的集合
    private static Map<Set<String>, Set<Map<Set<String>, Float>>> associationRules; //频繁关联规则集合

    private static Map<Integer, Set<String>> DB;
    private static int num;

    public AprioriAlgorithm(Map<Integer, Set<String>> txDatabase, Float minSup, Float minConf) {
        this.txDatabase = txDatabase;
        this.minSup = minSup;
        this.minConf = minConf;
        this.txDatabaseCount = this.txDatabase.size();
        freqItemSet = new TreeMap<>();
        freqItemSets = new HashMap<>();
        associationRules = new HashMap<>();
    }

    public static void main(String[] args) throws Exception {
        float minSup = 0.2f;
        float minConf = 0.7f;

        System.out.println("读取数据");
        String fn = "Apriori.txt";

        File file = new File(fn);
        FileReader fr = new FileReader(file);
        BufferedReader br = new BufferedReader(fr);
        DB = new HashMap<>();

        String line;
        String sp = ","; //分隔符

        while ((line = br.readLine()) != null) {
            String[] temp = line.trim().split(sp);
            Set<String> set = new TreeSet<>();
            for (int i = 1; i < temp.length; i++) {
                set.add(temp[i].trim());
            }
            num++;
            DB.put(num, set);
        }
        System.out.println(DB);
        AprioriAlgorithm apr = new AprioriAlgorithm(DB, minSup, minConf);
        apr.findAllFreqItemSet();
        apr.findAssociationRules();
    }

    public void findAllFreqItemSet() {
        // 频繁1-项集
        Map<Set<String>, Float> freqOneItemSet = find_Frequent_one_Itemsets();
        System.out.println("频繁1-项集：" + freqOneItemSet);
        freqItemSets.put(1, freqOneItemSet);

        // 频繁k-项集（k>1）
        int k = 2;
        while (true) {
            Set<Set<String>> candFreItemsets = apriori_Gen(k, freqItemSets.get(k - 1).keySet());
            Map<Set<String>, Float> freqKItemSetMap = getFreqKItemSet(k, candFreItemsets);
            if (!freqKItemSetMap.isEmpty()) {
                freqItemSets.put(k, freqKItemSetMap);
            } else {
                break;
            }
            System.out.println("频繁" + k + "-项集：" + freqKItemSetMap);
            k++;
        }
    }

    // 频繁一项集函数
    public Map<Set<String>, Float> find_Frequent_one_Itemsets() {
        Map<Set<String>, Float> L1 = new HashMap<>();
        Map<Set<String>, Integer> item1SetMap = new HashMap<>();
        Iterator<Map.Entry<Integer, Set<String>>> it = DB.entrySet().iterator();

        // 支持度计数，生成候选频繁1-项集
        while (it.hasNext()) {
            Map.Entry<Integer, Set<String>> entry = it.next();
            Set<String> itemSet = entry.getValue();
            for (String item : itemSet) {
                Set<String> key = new HashSet<String>();
                key.add(item.trim());
                if (!item1SetMap.containsKey(key)) {
                    item1SetMap.put(key, 1);
                } else {
                    int value = 1 + item1SetMap.get(key);
                    item1SetMap.put(key, value);
                }
            }
        }

        // 找出支持度大于minSup的频繁一项集
        Iterator<Map.Entry<Set<String>, Integer>> iter = item1SetMap.entrySet().iterator();
        while (iter.hasNext()) {
            Map.Entry<Set<String>, Integer> entry = iter.next();
            // 计算支持度
            Float support = new Float(entry.getValue().toString()) / (float) num;
            if (support >= minSup) {
                L1.put(entry.getKey(), support);
            }
        }
        return L1;
    }

    // 从K项频繁项集产生候选K+1项集函数
    public static Set<Set<String>> apriori_Gen(int k, Set<Set<String>> freqKItemSet) {
        Set<Set<String>> candFreqKItemSet = new HashSet<>();
        Iterator<Set<String>> it1 = freqKItemSet.iterator();
        while (it1.hasNext()) {
            Set<String> itemSet1 = it1.next();
            Iterator<Set<String>> it2 = freqKItemSet.iterator();
            while (it2.hasNext()) {
                Set<String> itemSet2 = it2.next();
                if (!itemSet1.equals(itemSet2)) {
                    // 连接步，k-项集中前k-2个项必须相同
                    Set<String> commItems = new HashSet<>();
                    commItems.addAll(itemSet1);
                    commItems.retainAll(itemSet2);
                    if (commItems.size() == k - 2) {
                        Set<String> candiItems = new HashSet<>();
                        candiItems.addAll(itemSet1);
                        candiItems.removeAll(itemSet2);
                        candiItems.addAll(itemSet2);
                        // 剪枝步，查看生成的K项集的任意K-1项集是否都在已获取的频繁K-1项 freqKItemSet中
                        if (!has_infrequent_subset(candiItems, freqKItemSet)) {
                            candFreqKItemSet.add(candiItems);
                        }
                    }
                }
            }
        }
        return candFreqKItemSet;
    }

    // 判断一个候选是否应该剪枝条
    private static boolean has_infrequent_subset(Set<String> itemSet, Set<Set<String>> freqKItemSet) {
        // 获取itemSet的所有k-1子集
        Set<Set<String>> subItemSet = new HashSet<>();
        Iterator<String> itr = itemSet.iterator();
        while (itr.hasNext()) {
            // 深拷贝
            Set<String> subItem = new HashSet<>();
            Iterator<String> it = itemSet.iterator();
            while (it.hasNext()) {
                subItem.add(it.next());
            }
            // 去掉一个项后即为k-1子集
            subItem.remove(itr.next());
            subItemSet.add(subItem);
        }
        Iterator<Set<String>> it = subItemSet.iterator();
        while (it.hasNext()) {
            if (!freqKItemSet.contains(it.next())) {
                return true;
            }
        }
        return false;
    }

    public Map<Set<String>, Float> getFreqKItemSet(int k, Set<Set<String>> candFreqKItemSet) {
        Map<Set<String>, Integer> candFreqKItemSetMap = new HashMap<>();
        // 扫描事物数据库
        Iterator<Map.Entry<Integer, Set<String>>> it = DB.entrySet().iterator();
        // 统计支持度

        while (it.hasNext()) {
            Map.Entry<Integer, Set<String>> entry = it.next();
            Iterator<Set<String>> iter = candFreqKItemSet.iterator();
            while (iter.hasNext()) {
                Set<String> s = iter.next();
                if (entry.getValue().containsAll(s)) {
                    if (!candFreqKItemSetMap.containsKey(s)) {
                        candFreqKItemSetMap.put(s, 1);
                    } else {
                        int value = 1 + candFreqKItemSetMap.get(s);
                        candFreqKItemSetMap.put(s, value);
                    }
                }
            }
        }

        // 计算支持度并生成最终的频繁k-项集
        Map<Set<String>, Float> freqKItemSetMap = new HashMap<>();
        Iterator<Map.Entry<Set<String>, Integer>> itr = candFreqKItemSetMap.entrySet().iterator();
        while (itr.hasNext()) {
            Map.Entry<Set<String>, Integer> entry = itr.next();
            // 计算支持度
            float support = new Float(entry.getValue().toString()) / num;
            if (support < minSup) { //如果不满足最小支持度，则删除
                itr.remove();
            } else {
                freqKItemSetMap.put(entry.getKey(), support);
            }
        }
        return freqKItemSetMap;
    }

    public void findAssociationRules() {
//        freqItemSets.remove(1); // 删除频繁1-项集
        Iterator<Map.Entry<Integer, Map<Set<String>, Float>>> it = freqItemSets.entrySet().iterator();
        while (it.hasNext()) {
            Map.Entry<Integer, Map<Set<String>, Float>> entry = it.next();
            for (Set<String> itemSet : entry.getValue().keySet()) {
                // 对每个频繁项集进行关联规则的挖掘
                int n = itemSet.size() / 2; // 根据集合的对称性，只需要得到一半的真子集
                for (int i = 1; i <= n; i++) {
                    // 得到频繁项集元素itemSet的作为条件的真子集集合
                    Set<Set<String>> subset = ProperSubsetCombination.getProperSubset(i, itemSet);
                    // 对条件的真子集集合中的每个条件项集，获取到对应的结论项集，从而进一步挖掘频繁关联规则
                    for (Set<String> conditionSet : subset) {
                        Set<String> conclusionSet = new HashSet<>();
                        conclusionSet.addAll(itemSet);
                        conclusionSet.removeAll(conditionSet); // 删除条件中存在的频繁项

                        int s1 = conditionSet.size();
                        int s2 = conclusionSet.size();

                        if (freqItemSets.get(s1) != null && freqItemSets.get(s2) != null) {
                            float sup1 = freqItemSets.get(s1).get(conditionSet);
                            float sup2 = freqItemSets.get(s2).get(conclusionSet);
                            if (freqItemSets.get(s1 + s2) == null) {
                                continue;
                            }

                            float sup = freqItemSets.get(s1 + s2).get(itemSet);

                            float conf1 = sup / sup1;
                            float conf2 = sup / sup2;

                            if (conf1 >= minConf) {
                                if (associationRules.get(conditionSet) == null) {
                                    // 如果不存在以该条件频繁项集为条件的关联规则
                                    Set<Map<Set<String>, Float>> conclusionSetSet = new HashSet<>();
                                    Map<Set<String>, Float> sets = new HashMap<>();
                                    sets.put(conclusionSet, conf1);
                                    conclusionSetSet.add(sets);
                                    associationRules.put(conditionSet, conclusionSetSet);
                                } else {
                                    Map<Set<String>, Float> sets = new HashMap<>();
                                    sets.put(conclusionSet, conf1);
                                    Set<Map<Set<String>, Float>> lastSet = associationRules.get(conditionSet);
                                    if (lastSet != null) {
                                        lastSet.add(sets);
                                    }
                                }
                            }

                            if (conf2 >= minConf) {
                                if (associationRules.get(conclusionSet) == null) {
                                    // 如果不存在以该结论频繁项集为条件的关联规则
                                    Set<Map<Set<String>, Float>> conclusionSetSet = new HashSet<>();
                                    Map<Set<String>, Float> sets = new HashMap<>();
                                    sets.put(conclusionSet, conf2);
                                    conclusionSetSet.add(sets);
                                    associationRules.put(conclusionSet, conclusionSetSet);
                                } else {
                                    Map<Set<String>, Float> sets = new HashMap<>();
                                    sets.put(conditionSet, conf2);
                                    Set<Map<Set<String>, Float>> lastSet = associationRules.get(conclusionSet);
                                    if (lastSet != null) {
                                        lastSet.add(sets);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        System.out.println();
        System.out.println("关联规则（强规则）：");

        for (Map.Entry<Set<String>, Set<Map<Set<String>, Float>>> entry : associationRules.entrySet()) {
            Set<String> key = entry.getKey();
            Set<Map<Set<String>, Float>> value = entry.getValue();
            System.out.print(key);
            System.out.print(" : ");
            System.out.println(value);
        }
    }
}
