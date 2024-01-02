using System.Collections;
using System.Collections.Generic;
using UnityEngine;


//�˺�����
public enum SkillDamageType
{
    PHYSICAL,//����
    MAGIC//����
}

//�����ͷŶ�������
public enum SkillOBJECTType
{
    TEAMMATE,//����
    ENEMY,//����
    NO,//��Ŀ��
    GROUND//����
}

[CreateAssetMenu(fileName = "New Skill", menuName = "Skills/New Skill")]
public class SkillData : ScriptableObject
{
    //����
    public int mana;
    //���
    public float skillRange;

    [Header("Damage")]
    //�����˺�
    public int baseDamage;

    //�ӳ�ϵ��
    public float HPFactor;//Ѫ��
    public float atkFactor;//����
    public float SPFactor;//��ǿ

    //�˺�����
    public SkillDamageType skillDamageType;

    public float CD;

    [TextArea]//����˵��
    public string skillInfo;

    [Header("Buff")]
    public int atkPlus;
    public int SPPlus;
    public float atkPlusPercent;
    public float SPPlusPercent;
    public float HPRecoverPlus;
    public float MPRecoverPlus;
    public int defencePlus;
    public int magicDefencePlus;
    public float contiTime;
}
